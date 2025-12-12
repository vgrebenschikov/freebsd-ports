--- show.c.orig	2025-12-12 12:33:48.145954000 +0100
+++ show.c	2025-12-12 12:32:50.349504000 +0100
@@ -401,39 +401,39 @@
 	 } else if (!strcmp(param, "h1")) {
 		if (with_interface)
 			printf("%s\t", device->name);
-		printf("%s\n", device->init_packet_magic_header);
+		printf("%s\n", device->init_packet_magic_header?:"0");
 	 } else if (!strcmp(param, "h2")) {
 		if (with_interface)
 			printf("%s\t", device->name);
-		printf("%s\n", device->response_packet_magic_header);
+		printf("%s\n", device->response_packet_magic_header?:"0");
 	 } else if (!strcmp(param, "h3")) {
 		if (with_interface)
 			printf("%s\t", device->name);
-		printf("%s\n", device->underload_packet_magic_header);
+		printf("%s\n", device->underload_packet_magic_header?:"0");
 	 } else if (!strcmp(param, "h4")) {
 		if (with_interface)
 			printf("%s\t", device->name);
-		printf("%s\n", device->transport_packet_magic_header);
+		printf("%s\n", device->transport_packet_magic_header?:"0");
 	} else if (!strcmp(param, "i1")) {
 		if (with_interface)
 			printf("%s\t", device->name);
-		printf("%s\n", device->i1);
+		printf("%s\n", device->i1?:"");
 	} else if (!strcmp(param, "i2")) {
 		if (with_interface)
 			printf("%s\t", device->name);
-		printf("%s\n", device->i2);
+		printf("%s\n", device->i2?:"");
 	} else if (!strcmp(param, "i3")) {
 		if (with_interface)
 			printf("%s\t", device->name);
-		printf("%s\n", device->i3);
+		printf("%s\n", device->i3?:"");
 	} else if (!strcmp(param, "i4")) {
 		if (with_interface)
 			printf("%s\t", device->name);
-		printf("%s\n", device->i4);
+		printf("%s\n", device->i4?:"");
 	} else if (!strcmp(param, "i5")) {
 		if (with_interface)
 			printf("%s\t", device->name);
-		printf("%s\n", device->i5);
+		printf("%s\n", device->i5?:"");
 	 } else if (!strcmp(param, "endpoints")) {
 		for_each_wgpeer(device, peer) {
 			if (with_interface)
