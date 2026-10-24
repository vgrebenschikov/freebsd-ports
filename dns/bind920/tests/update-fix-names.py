#!/usr/bin/env python3
"""Integration test against a built named; no third-party Python dependencies.
Usage: python3 tests/update-fix-names.py /path/to/bin/named/named
Starts an isolated server on an ephemeral loopback port; never reloads production.
"""
import hashlib
import hmac
import socket
import struct
import subprocess
import sys
import tempfile
import time
from pathlib import Path


def name(text):
    return b''.join(bytes([len(x)]) + x for x in text.encode().rstrip(b'.').split(b'.')) + b'\0'


def rr(owner, typ, cls=1, data=b'', ttl=0):
    return name(owner) + struct.pack('!HHIH', typ, cls, ttl, len(data)) + data


def packet(zone, updates=(), prerequisites=()):
    return (struct.pack('!6H', 1234, 5 << 11, 1, len(prerequisites), len(updates), 0)
            + name(zone) + struct.pack('!HH', 6, 1)
            + b''.join(prerequisites) + b''.join(updates))


def exchange(port, data):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        sock.settimeout(1)
        sock.sendto(data, ('127.0.0.1', port))
        return sock.recv(65535)


def signed(data):
    key = name('test-key')
    algorithm = name('hmac-sha256')
    stamp = int(time.time()).to_bytes(6, 'big')
    variables = (key + struct.pack('!HI', 255, 0) + algorithm + stamp
                 + struct.pack('!HHH', 300, 0, 0))
    mac = hmac.new(b'0123456789abcdef', data + variables, hashlib.sha256).digest()
    rdata = algorithm + stamp + struct.pack('!HH', 300, len(mac)) + mac + struct.pack('!HHH', 1234, 0, 0)
    return data[:10] + struct.pack('!H', 1) + data[12:] + rr('test-key', 250, 255, rdata)


def update(port, zone, updates=(), prerequisites=(), code=0, sign=False):
    data = packet(zone, updates, prerequisites)
    response = exchange(port, signed(data) if sign else data)
    actual = struct.unpack('!H', response[2:4])[0] & 15
    assert actual == code, (zone, code, actual)


def query(port, owner, typ, exists=True):
    response = exchange(port, struct.pack('!6H', 1234, 0, 1, 0, 0, 0)
                        + name(owner) + struct.pack('!HH', typ, 1))
    count = struct.unpack('!H', response[6:8])[0]
    assert (count > 0) == exists, (owner, typ, count)
    return response


def main():
    binary = str(Path(sys.argv[1]).resolve())
    with tempfile.TemporaryDirectory(prefix='bind-fix-names-') as directory:
        root = Path(directory)
        with socket.socket() as sock:
            sock.bind(('127.0.0.1', 0))
            port = sock.getsockname()[1]
        zones = [('dyn.test', True, True), ('2.22.172.in-addr.arpa', True, True),
                 ('off.test', False, True), ('deny.test', True, False), ('ssu.test', True, True)]
        conf = (f'options {{ directory "{directory}"; listen-on port {port} {{ 127.0.0.1; }}; '
                'listen-on-v6 { none; }; recursion no; dnssec-validation no; '
                'pid-file "named.pid"; session-keyfile "session.key"; }; controls {};\n'
                'key test-key { algorithm hmac-sha256; secret "MDEyMzQ1Njc4OWFiY2RlZg=="; };\n')
        for zone, enabled, allowed in zones:
            (root / zone).write_text(f'$TTL 60\n@ SOA ns.{zone}. hostmaster.{zone}. '
                                    f'(1 60 60 3600 60)\n@ NS ns.{zone}.\nns A 127.0.0.1\n')
            conf += (f'zone "{zone}" {{ type primary; file "{zone}"; '
                      + (
                         'update-policy { grant test-key name good-name.ssu.test A; }; '
                         if zone == 'ssu.test' else
                         f'allow-update {{ {"127.0.0.1" if allowed else "none"}; }}; ')
                     + ('update-fix-names yes; ' if enabled else '')
                     + 'check-names fail; };\n')
        (root / 'named.conf').write_text(conf)
        with (root / 'log').open('w+') as log:
            server = subprocess.Popen([binary, '-g', '-c', str(root / 'named.conf'), '-n', '1'],
                                      stdout=log, stderr=log)
            try:
                for _ in range(100):
                    if server.poll() is not None:
                        raise RuntimeError('named failed to start')
                    try:
                        query(port, 'ns.dyn.test', 1)
                        break
                    except (OSError, AssertionError):
                        time.sleep(.1)
                else:
                    raise RuntimeError('named startup timeout')
                address = socket.inet_aton('172.22.2.81')
                bad = 'Meross Smart Plug.dyn.test'
                good = 'Meross-Smart-Plug.dyn.test'
                # Cisco-style TXT prerequisites/ownership, A and AAAA additions.
                update(port, 'dyn.test', [rr(bad, 1, data=address, ttl=60),
                       rr(bad, 16, data=b'\x03tag', ttl=60),
                       rr(bad, 28, data=socket.inet_pton(socket.AF_INET6, '::81'), ttl=60)],
                       [rr(bad, 255, cls=254)])
                query(port, good, 1)
                query(port, good, 28)
                query(port, bad, 1, False)
                update(port, 'dyn.test', prerequisites=[rr(bad, 16, data=b'\x03tag')])
                # Reverse RDATA is transformed with the same rules.
                rev = '81.2.22.172.in-addr.arpa'
                update(port, '2.22.172.in-addr.arpa', [rr(rev, 12, data=name(bad), ttl=60)])
                assert name(good) in query(port, rev, 12)
                update(port, '2.22.172.in-addr.arpa', [rr(rev, 12, cls=254, data=name(bad))])
                query(port, rev, 12, False)
                # Specific-RR, RRset and whole-owner deletions use the original name.
                update(port, 'dyn.test', [rr(bad, 1, cls=254, data=address)])
                query(port, good, 1, False)
                update(port, 'dyn.test', [rr(bad, 28, cls=255)])
                query(port, good, 28, False)
                update(port, 'dyn.test', [rr(bad, 255, cls=255)])
                query(port, good, 16, False)
                # Boundaries, underscores, UTF-8 bytes, and idempotence.
                edge = '-bad_\u00e9-.dyn.test'
                fixed = 'xbad---x.dyn.test'
                update(port, 'dyn.test', [rr(edge, 1, data=address, ttl=60)])
                query(port, fixed, 1)
                update(port, 'dyn.test', [rr(fixed, 1, cls=254, data=address)])
                query(port, fixed, 1, False)
                # Default off, ACL refusal and NOTZONE remain enforced.
                update(port, 'off.test', [rr('bad name.off.test', 1, data=address, ttl=60)], code=5)
                update(port, 'deny.test', [rr('bad name.deny.test', 1, data=address, ttl=60)], code=5)
                update(port, 'dyn.test', [rr('bad name.outside.test', 1, data=address, ttl=60)], code=10)
                # Authorization checks the transformed name, using genuine TSIG.
                update(port, 'ssu.test', [rr('good name.ssu.test', 1, data=address, ttl=60)], sign=True)
                query(port, 'good-name.ssu.test', 1)
                update(port, 'ssu.test', [rr('other name.ssu.test', 1, data=address, ttl=60)], sign=True, code=5)
                query(port, 'other-name.ssu.test', 1, False)
                update(port, 'dyn.test', [rr('*.dyn.test', 1, data=address, ttl=60)])
                query(port, '*.dyn.test', 1)
                print('PASS: add A/AAAA/TXT/PTR, prerequisites, deletions, normalization, default off, ACL, TSIG/update-policy, wildcard, NOTZONE')
            except Exception:
                log.flush()
                log.seek(0)
                print(log.read(), file=sys.stderr)
                raise
            finally:
                server.terminate()
                server.wait(timeout=15)


if __name__ == '__main__':
    main()
