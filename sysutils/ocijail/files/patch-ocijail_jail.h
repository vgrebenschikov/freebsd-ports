--- ocijail/jail.h.orig	2026-02-09 09:25:22 UTC
+++ ocijail/jail.h
@@ -13,8 +13,8 @@ struct jail {
     };
 
     struct config {
-        using value =
-            std::variant<std::monostate, std::string, uint32_t, int32_t, ns>;
+        using value = std::variant<std::monostate, std::string, uint32_t,
+                                   int32_t, ns, std::vector<uint8_t>>;
         void set(const std::string& key, const value& value = std::monostate{});
         value& at(const std::string& key) { return params_.at(key); }
 
