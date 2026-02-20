--- ocijail/create.cpp.orig	2026-02-09 09:36:28 UTC
+++ ocijail/create.cpp
@@ -1,4 +1,6 @@
 #include <fcntl.h>
+#include <netinet/in.h>
+#include <arpa/inet.h>
 #include <sys/mount.h>
 #include <sys/socket.h>
 #include <sys/stat.h>
@@ -214,6 +216,8 @@ void create::run() {
     // Get the parent jail name and requested vnet type (if any)
     std::optional<std::string> parent_jail;
     auto vnet = jail::INHERIT;
+    std::optional<std::string> ip4_addr;
+    std::optional<std::string> ip6_addr;
     if (config.contains("annotations")) {
         auto config_annotations = config["annotations"];
         if (config_annotations.contains("org.freebsd.parentJail")) {
@@ -232,6 +236,16 @@ void create::run() {
                     "bad value for org.freebsd.jail.vnet: " + val);
             }
         }
+        if (vnet == jail::INHERIT) {
+            if (config_annotations.contains("org.freebsd.jail.ip4.addr")) {
+                ip4_addr = config_annotations["org.freebsd.jail.ip4.addr"];
+            }
+            if (config_annotations.contains("org.freebsd.jail.ip6.addr")) {
+                ip6_addr = config_annotations["org.freebsd.jail.ip6.addr"];
+            } else if (config_annotations.contains("org.freebsd.jail.ip6.add")) {
+                ip6_addr = config_annotations["org.freebsd.jail.ip6.add"];
+            }
+        }
     }
 
     // Create a jail config from the OCI config
@@ -255,8 +269,62 @@ void create::run() {
     if (vnet == jail::NEW) {
         jconf.set("vnet", vnet);
     } else {
-        jconf.set("ip4", jail::INHERIT);
-        jconf.set("ip6", jail::INHERIT);
+        if (ip4_addr) {
+            std::vector<uint8_t> addrs;
+            std::string::size_type start = 0;
+            while (start < ip4_addr->size()) {
+                auto end = ip4_addr->find(',', start);
+                auto token = ip4_addr->substr(
+                    start, end == std::string::npos ? std::string::npos
+                                                    : end - start);
+                if (!token.empty()) {
+                    in_addr addr{};
+                    if (inet_pton(AF_INET, token.c_str(), &addr) != 1) {
+                        throw std::runtime_error(
+                            "bad value for org.freebsd.jail.ip4.addr: " +
+                            token);
+                    }
+                    auto* p = reinterpret_cast<uint8_t*>(&addr);
+                    addrs.insert(addrs.end(), p, p + sizeof(addr));
+                }
+                if (end == std::string::npos) {
+                    break;
+                }
+                start = end + 1;
+            }
+            jconf.set("ip4", jail::INHERIT);
+            jconf.set("ip4.addr", addrs);
+        } else {
+            jconf.set("ip4", jail::INHERIT);
+        }
+        if (ip6_addr) {
+            std::vector<uint8_t> addrs;
+            std::string::size_type start = 0;
+            while (start < ip6_addr->size()) {
+                auto end = ip6_addr->find(',', start);
+                auto token = ip6_addr->substr(
+                    start, end == std::string::npos ? std::string::npos
+                                                    : end - start);
+                if (!token.empty()) {
+                    in6_addr addr{};
+                    if (inet_pton(AF_INET6, token.c_str(), &addr) != 1) {
+                        throw std::runtime_error(
+                            "bad value for org.freebsd.jail.ip6.addr: " +
+                            token);
+                    }
+                    auto* p = reinterpret_cast<uint8_t*>(&addr);
+                    addrs.insert(addrs.end(), p, p + sizeof(addr));
+                }
+                if (end == std::string::npos) {
+                    break;
+                }
+                start = end + 1;
+            }
+            jconf.set("ip6", jail::INHERIT);
+            jconf.set("ip6.addr", addrs);
+        } else {
+            jconf.set("ip6", jail::INHERIT);
+        }
     }
     if (config.contains("hostname")) {
         jconf.set("host.hostname", config["hostname"].get<std::string>());
