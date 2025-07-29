--- lib/vrf.c.orig	2025-07-29 11:34:38 UTC
+++ lib/vrf.c
@@ -187,10 +187,6 @@ struct vrf *vrf_get(vrf_id_t vrf_id, const char *name)
 		strlcpy(vrf->name, name, sizeof(vrf->name));
 		RB_INSERT(vrf_name_head, &vrfs_by_name, vrf);
 
-		/* We have a name now so we can have state */
-		if (vrf_notify_oper_changes)
-			vrf->state = nb_op_update_pathf(NULL, "/frr-vrf:lib/vrf[name=\"%s\"]/state",
-							NULL, vrf->name);
 	}
 	/* Update state before hook call */
 	if (vrf->state)
@@ -1051,7 +1047,10 @@ lib_vrf_state_id_get_elem(struct nb_cb_get_elem_args *
 {
 	struct vrf *vrfp = (struct vrf *)args->list_entry;
 
-	return yang_data_new_uint32(args->xpath, vrfp->vrf_id);
+	if (vrfp && vrfp->vrf_id != VRF_UNKNOWN)
+ 		return yang_data_new_uint32(args->xpath, vrfp->vrf_id);
+
+ 	return NULL;
 }
 
 /*
@@ -1062,7 +1061,10 @@ lib_vrf_state_active_get_elem(struct nb_cb_get_elem_ar
 {
 	struct vrf *vrfp = (struct vrf *)args->list_entry;
 
-	return yang_data_new_bool(args->xpath, vrfp->status == VRF_ACTIVE ? true : false);
+	if (vrfp && vrfp->vrf_id != VRF_UNKNOWN)
+ 		return yang_data_new_bool(args->xpath, CHECK_FLAG(vrfp->status, VRF_ACTIVE));
+
+ 	return NULL;
 }
 
 /* clang-format off */
