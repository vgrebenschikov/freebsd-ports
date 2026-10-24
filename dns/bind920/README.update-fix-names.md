# Local BIND 9.20.30 patch: DDNS hostname normalization

`files/patch-ddns-update-fix-names` adds a primary-zone-only boolean option,
`update-fix-names`, disabled by default. This is a local extension, not an ISC
BIND feature. Enable it only in dedicated DHCP hostname zones.

Inside the existing zones in `view "bricks"` add:

```conf
zone "dyn.fbsd.ru" {
    // existing type, file and update authorization settings
    update-fix-names yes;
    check-names fail;
};
zone "2.22.172.in-addr.arpa" {
    // existing type, file and update authorization settings
    update-fix-names yes;
    check-names fail;
};
```

Do the same for other reverse zones populated by Cisco. Retain the existing
`allow-update` or `update-policy`; the new option grants no update permissions.
These snippets show additions, not complete zone definitions.

## Transformation

* `Meross\032Smart\032Plug.dyn.fbsd.ru` becomes
  `Meross-Smart-Plug.dyn.fbsd.ru`.
* ASCII letters and digits are retained, as are interior hyphens.
* Every other byte becomes `-` inside a label, or `x` at a label boundary.
  Leading/trailing hyphens also become `x`. Example: `_plug_` -> `xplugx`.
* Case, label lengths, and label boundaries are preserved. UTF-8 is treated
  as bytes, not transliterated or converted to IDNA. Repeated hyphens remain.
* Every owner name below the zone apex is normalized, for all RR types,
  including TXT ownership records, ANY deletions, and prerequisites. The
  configured zone suffix is retained. A leading wildcard label is retained.
* PTR targets are normalized in all their labels, including on specific-RR
  deletion and value-dependent prerequisites. Other RDATA is unchanged.
* The original parsed message is never modified. Normalized copies are used
  consistently during authorization, prerequisite evaluation and database
  updates. Records originally outside the zone remain outside and are rejected.

## Limits

This is a many-to-one transformation: `a b`, `a_b` and `a-b` all map to `a-b`.
It does not disambiguate devices, add MAC suffixes, or prevent one authorized
DHCP client from overwriting another client's name. This also changes RFC 2136
name semantics intentionally. Use only where that behavior is wanted.

Because all owner names are treated as hostnames, do not enable it in zones
containing service discovery names such as `_sip._tcp` or `_acme-challenge`.
It does not normalize CNAME/MX/SRV/NS targets, loaded zone files, queries,
transfers, or existing records. Existing invalid records require separate cleanup;
turning this on does not migrate them. Direct DNS queries must use the new name.

## Build and verification

The FreeBSD port applies `files/patch-*` automatically. Rebuild/package using
normal ports procedures; this work does not install or restart production named.
After installing the resulting package, validate configuration with
`named-checkconf` before reloading.

Run the isolated integration test against a freshly built binary:

```sh
python3 tests/update-fix-names.py /path/to/bind-9.20.30/bin/named/named
```

The test uses only Python's standard library and starts a temporary named on an
unprivileged loopback port. It exercises A/AAAA/TXT/PTR, prerequisites, deletion,
normalization boundaries, default-off behavior, ACL refusal, TSIG/update-policy authorization, wildcard preservation and zone
boundaries.
