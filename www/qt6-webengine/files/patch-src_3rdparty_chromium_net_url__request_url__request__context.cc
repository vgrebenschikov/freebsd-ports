--- src/3rdparty/chromium/net/url_request/url_request_context.cc.orig	2024-06-17 12:56:06 UTC
+++ src/3rdparty/chromium/net/url_request/url_request_context.cc
@@ -121,7 +121,7 @@ const HttpNetworkSessionContext* URLRequestContext::Ge
 // TODO(crbug.com/40118868): Revisit once build flag switch of lacros-chrome is
 // complete.
 #if !BUILDFLAG(IS_WIN) && \
-    !(BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS))
+    !(BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS_LACROS) || BUILDFLAG(IS_BSD))
 std::unique_ptr<URLRequest> URLRequestContext::CreateRequest(
     const GURL& url,
     RequestPriority priority,
