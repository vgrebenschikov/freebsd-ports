--- src/3rdparty/chromium/content/browser/compositor/viz_process_transport_factory.cc.orig	2024-07-30 11:12:21 UTC
+++ src/3rdparty/chromium/content/browser/compositor/viz_process_transport_factory.cc
@@ -110,7 +110,7 @@ class HostDisplayClient : public viz::HostDisplayClien
   HostDisplayClient& operator=(const HostDisplayClient&) = delete;
 
   // viz::HostDisplayClient:
-#if BUILDFLAG(IS_LINUX) && BUILDFLAG(IS_OZONE_X11)
+#if (BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_BSD)) && BUILDFLAG(IS_OZONE_X11)
   void DidCompleteSwapWithNewSize(const gfx::Size& size) override {
     compositor_->OnCompleteSwapWithNewSize(size);
   }
