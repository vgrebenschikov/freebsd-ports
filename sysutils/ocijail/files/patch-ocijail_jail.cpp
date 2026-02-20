--- ocijail/jail.cpp.orig	2026-02-09 09:25:18 UTC
+++ ocijail/jail.cpp
@@ -2,9 +2,11 @@
 
 #include <sys/jail.h>
 #include <cassert>
+#include <iomanip>
 #include <string>
 #include <system_error>
 #include <vector>
+#include <iostream>
 
 #include "ocijail/jail.h"
 
@@ -16,6 +18,8 @@ void jail::config::set(const std::string& key, const v
         assert(std::holds_alternative<uint32_t>(val));
     } else if (key == "ip4" || key == "ip6") {
         assert(std::holds_alternative<ns>(val));
+    } else if (key == "ip4.addr" || key == "ip6.addr") {
+        assert(std::holds_alternative<std::vector<uint8_t>>(val));
     } else if (key == "host" || key == "vnet") {
         assert(std::holds_alternative<ns>(val) &&
                std::get<ns>(val) != DISABLED);
@@ -101,11 +105,14 @@ std::vector<iovec> jail::get_iovec(config& jconf) {
         } else if (auto p = std::get_if<int32_t>(&val)) {
             jiov.emplace_back(
                 iovec{reinterpret_cast<void*>(p), sizeof(int32_t)});
-        } else if (auto p = std::get_if<std::monostate>(&val)) {
+        } else if (std::holds_alternative<std::monostate>(val)) {
             jiov.emplace_back(iovec{nullptr, 0});
         } else if (auto p = std::get_if<ns>(&val)) {
             jiov.emplace_back(
                 iovec{reinterpret_cast<void*>(p), sizeof(uint32_t)});
+        } else if (auto p = std::get_if<std::vector<uint8_t>>(&val)) {
+            jiov.emplace_back(iovec{reinterpret_cast<void*>(p->data()),
+                                    static_cast<size_t>(p->size())});
         }
     }
     return jiov;
