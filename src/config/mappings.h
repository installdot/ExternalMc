#pragma once

/*
 * Mapping Table — Minecraft 1.21 (Fabric Intermediary)
 *
 * Fabric uses Intermediary names at runtime in production.
 * All class paths use JNI '/' separator format.
 */

namespace Mappings {

    // ─── Classes ────────────────────────────────────────────────────────
    inline constexpr const char* Minecraft_Class    = "net/minecraft/class_310";
    inline constexpr const char* Entity_Class       = "net/minecraft/class_1297";
    inline constexpr const char* LivingEntity_Class = "net/minecraft/class_1309";
    inline constexpr const char* LocalPlayer_Class  = "net/minecraft/class_746";
    inline constexpr const char* ClientLevel_Class  = "net/minecraft/class_638";
    inline constexpr const char* Vec3_Class         = "net/minecraft/class_243";
    inline constexpr const char* AABB_Class         = "net/minecraft/class_238";
    inline constexpr const char* Player_Class       = "net/minecraft/class_1657";
    inline constexpr const char* List_Class         = "java/util/List";
    inline constexpr const char* GameRenderer_Class = "net/minecraft/class_757";
    inline constexpr const char* Connection_Class   = "net/minecraft/class_2535";
    inline constexpr const char* RenderSystem_Class = "com/mojang/blaze3d/systems/RenderSystem"; // Unobfuscated
    inline constexpr const char* Matrix4f_Class     = "org/joml/Matrix4f";
    inline constexpr const char* GameProfile_Class  = "com/mojang/authlib/GameProfile";
    inline constexpr const char* Component_Class    = "net/minecraft/class_2561";
    inline constexpr const char* AbstractClientPlayer_Class = "net/minecraft/class_742";
    inline constexpr const char* ItemEntity_Class   = "net/minecraft/class_1542";
    inline constexpr const char* ArmorStand_Class   = "net/minecraft/class_1531";
    inline constexpr const char* MinecartChest_Class= "net/minecraft/class_1694";
    inline constexpr const char* Camera_Class       = "net/minecraft/class_4184";
    inline constexpr const char* Options_Class      = "net/minecraft/class_315";
    inline constexpr const char* Level_Class        = "net/minecraft/class_1937";
    inline constexpr const char* Mouse_Class        = "net/minecraft/class_312";

    // ─── Minecraft Methods ─────────────────────────────────────────────
    inline constexpr const char* MC_getInstance     = "method_1551";
    inline constexpr const char* MC_getInstance_Sig = "()Lnet/minecraft/class_310;";

    // ─── Minecraft Fields ──────────────────────────────────────────────
    inline constexpr const char* MC_player          = "field_1724";
    inline constexpr const char* MC_player_Sig      = "Lnet/minecraft/class_746;";
    inline constexpr const char* MC_level           = "field_1687";
    inline constexpr const char* MC_level_Sig       = "Lnet/minecraft/class_638;";
    inline constexpr const char* MC_gameRenderer    = "field_1773";
    inline constexpr const char* MC_gameRenderer_Sig = "Lnet/minecraft/class_757;";
    inline constexpr const char* MC_options          = "field_1690";
    inline constexpr const char* MC_options_Sig      = "Lnet/minecraft/class_315;";
    inline constexpr const char* MC_mouse           = "field_1704";
    inline constexpr const char* MC_mouse_Sig       = "Lnet/minecraft/class_312;";

    // ─── Mouse Methods ─────────────────────────────────────────────────
    inline constexpr const char* Mouse_lockCursor   = "method_1612";
    inline constexpr const char* Mouse_lockCursor_Sig = "()V";
    inline constexpr const char* Mouse_unlockCursor = "method_1610";
    inline constexpr const char* Mouse_unlockCursor_Sig = "()V";

    // ─── GameRenderer Methods ────────────────────────────────────────
    inline constexpr const char* GR_getMainCamera     = "method_3196";
    inline constexpr const char* GR_getMainCamera_Sig = "()Lnet/minecraft/class_4184;";
    inline constexpr const char* GR_getFov            = "method_3199";
    inline constexpr const char* GR_getFov_Sig        = "(Lnet/minecraft/class_4184;FZ)F";

    // ─── Camera Methods ──────────────────────────────────────────────
    inline constexpr const char* Camera_getPosition     = "method_19326";
    inline constexpr const char* Camera_getPosition_Sig = "()Lnet/minecraft/class_243;";
    inline constexpr const char* Camera_getXRot         = "method_19330";
    inline constexpr const char* Camera_getXRot_Sig     = "()F";
    inline constexpr const char* Camera_getYRot         = "method_19329";
    inline constexpr const char* Camera_getYRot_Sig     = "()F";

    // ─── Options Fields ──────────────────────────────────────────────
    inline constexpr const char* Options_fov            = "field_1849"; // In Fabric 1.21, this is field_1849 SimpleOption
    // SimpleOption is class_7172. get() is method_41753

    // ─── Entity Methods ────────────────────────────────────────────────
    inline constexpr const char* Entity_getX        = "method_23317";
    inline constexpr const char* Entity_getX_Sig    = "()D";
    inline constexpr const char* Entity_getY        = "method_23318";
    inline constexpr const char* Entity_getY_Sig    = "()D";
    inline constexpr const char* Entity_getZ        = "method_23321";
    inline constexpr const char* Entity_getZ_Sig    = "()D";

    inline constexpr const char* Entity_isAlive     = "method_5805";
    inline constexpr const char* Entity_isAlive_Sig = "()Z";
    inline constexpr const char* Entity_getId       = "method_5628";
    inline constexpr const char* Entity_getId_Sig   = "()I";

    inline constexpr const char* Entity_getBoundingBox     = "method_5829";
    inline constexpr const char* Entity_getBoundingBox_Sig = "()Lnet/minecraft/class_238;";

    inline constexpr const char* Entity_getDeltaMovement     = "method_18798";
    inline constexpr const char* Entity_getDeltaMovement_Sig = "()Lnet/minecraft/class_243;";

    inline constexpr const char* Entity_setDeltaMovement     = "method_18799";
    inline constexpr const char* Entity_setDeltaMovement_Sig = "(Lnet/minecraft/class_243;)V";

    inline constexpr const char* Entity_getYRot     = "method_36454";
    inline constexpr const char* Entity_getYRot_Sig = "()F";
    inline constexpr const char* Entity_getXRot     = "method_36455";
    inline constexpr const char* Entity_getXRot_Sig = "()F";

    inline constexpr const char* Entity_setYRot     = "method_36456";
    inline constexpr const char* Entity_setYRot_Sig = "(F)V";
    inline constexpr const char* Entity_setXRot     = "method_36457";
    inline constexpr const char* Entity_setXRot_Sig = "(F)V";

    inline constexpr const char* Entity_getName     = "method_5476";
    inline constexpr const char* Entity_getName_Sig = "()Lnet/minecraft/class_2561;";
    inline constexpr const char* Entity_getScoreboardName     = "method_5820";
    inline constexpr const char* Entity_getScoreboardName_Sig = "()Ljava/lang/String;";
    inline constexpr const char* Entity_setSharedFlag     = "method_5728";
    inline constexpr const char* Entity_setSharedFlag_Sig = "(IZ)V";
    inline constexpr const char* Entity_getSharedFlag     = "method_5666";
    inline constexpr const char* Entity_getSharedFlag_Sig = "(I)Z";

    // ─── LivingEntity Methods ──────────────────────────────────────────
    inline constexpr const char* LivingEntity_getHealth     = "method_6032";
    inline constexpr const char* LivingEntity_getHealth_Sig = "()F";
    inline constexpr const char* LivingEntity_getMaxHealth     = "method_6063";
    inline constexpr const char* LivingEntity_getMaxHealth_Sig = "()F";

    // ─── Player Methods ────────────────────────────────────────────────
    inline constexpr const char* Player_getGameProfile     = "method_7334";
    inline constexpr const char* Player_getGameProfile_Sig = "()Lcom/mojang/authlib/GameProfile;";
    
    // PlayerAbilities (class_1656)
    inline constexpr const char* Player_abilities     = "field_7503";
    inline constexpr const char* Player_abilities_Sig = "Lnet/minecraft/class_1656;";
    inline constexpr const char* PlayerAbilities_flying = "field_7479";
    inline constexpr const char* PlayerAbilities_flying_Sig = "Z";

    // GameProfile.getName() — external library, never obfuscated
    inline constexpr const char* GameProfile_getName       = "getName";
    inline constexpr const char* GameProfile_getName_Sig   = "()Ljava/lang/String;";

    // ─── ClientLevel / Level ──────────────────────────────────────────
    inline constexpr const char* Level_players      = "method_18456";
    inline constexpr const char* Level_players_Sig  = "()Ljava/util/List;";
    
    inline constexpr const char* Level_getBlockState = "method_8320";
    inline constexpr const char* Level_getBlockState_Sig = "(Lnet/minecraft/class_2338;)Lnet/minecraft/class_2680;";

    // ─── Block & BlockState ──────────────────────────────────────────
    inline constexpr const char* MutableBlockPos_Class = "net/minecraft/class_2338$class_2339";
    inline constexpr const char* MutableBlockPos_Init = "<init>";
    inline constexpr const char* MutableBlockPos_Init_Sig = "(III)V";
    inline constexpr const char* MutableBlockPos_set = "method_10103";
    inline constexpr const char* MutableBlockPos_set_Sig = "(III)Lnet/minecraft/class_2338$class_2339;";
    
    inline constexpr const char* BlockState_Class = "net/minecraft/class_2680";
    inline constexpr const char* BlockState_getBlock = "method_26204";
    inline constexpr const char* BlockState_getBlock_Sig = "()Lnet/minecraft/class_2248;";

    // ─── Entity Physics ────────────────────────────────────────────────
    inline constexpr const char* Entity_isInWater     = "method_5799";
    inline constexpr const char* Entity_isInWater_Sig = "()Z";

    inline constexpr const char* Entity_onGround     = "method_24828";
    inline constexpr const char* Entity_onGround_Sig = "()Z";
    inline constexpr const char* Entity_horizontalCollision = "field_28646"; // Wait, might be field_28646
    inline constexpr const char* Entity_horizontalCollision_Sig = "Z";
    
    // ─── ClientPacketListener ──────────────────────────────────────────
    inline constexpr const char* ClientPacketListener_Class = "net/minecraft/class_634";
    inline constexpr const char* MC_getNetworkHandler = "method_1562";
    inline constexpr const char* MC_getNetworkHandler_Sig = "()Lnet/minecraft/class_634;";
    
    inline constexpr const char* ClientPacketListener_sendPacket = "method_52787";
    inline constexpr const char* ClientPacketListener_sendPacket_Sig = "(Lnet/minecraft/class_2596;)V";
    
    inline constexpr const char* PlayerMoveC2SPacket_Class = "net/minecraft/class_2828";
    inline constexpr const char* PlayerMoveC2SPacket_PositionAndOnGround_Class = "net/minecraft/class_2828$class_2829";
    inline constexpr const char* PlayerMoveC2SPacket_PositionAndOnGround_Init = "<init>";
    inline constexpr const char* PlayerMoveC2SPacket_PositionAndOnGround_Init_Sig = "(DDDZ)V";

    // ─── AABB ──────────────────────────────────────────────────────────
    inline constexpr const char* AABB_minX          = "field_1323";
    inline constexpr const char* AABB_minX_Sig      = "D";
    inline constexpr const char* AABB_minY          = "field_1322";
    inline constexpr const char* AABB_minY_Sig      = "D";
    inline constexpr const char* AABB_minZ          = "field_1321";
    inline constexpr const char* AABB_minZ_Sig      = "D";
    inline constexpr const char* AABB_maxX          = "field_1320";
    inline constexpr const char* AABB_maxX_Sig      = "D";
    inline constexpr const char* AABB_maxY          = "field_1325";
    inline constexpr const char* AABB_maxY_Sig      = "D";
    inline constexpr const char* AABB_maxZ          = "field_1324";
    inline constexpr const char* AABB_maxZ_Sig      = "D";

    // ─── Vec3 ──────────────────────────────────────────────────────────
    inline constexpr const char* Vec3_x             = "field_1352";
    inline constexpr const char* Vec3_x_Sig         = "D";
    inline constexpr const char* Vec3_y             = "field_1351";
    inline constexpr const char* Vec3_y_Sig         = "D";
    inline constexpr const char* Vec3_z             = "field_1350";
    inline constexpr const char* Vec3_z_Sig         = "D";

    // ─── Component ─────────────────────────────────────────────────────
    inline constexpr const char* Component_getString    = "method_10851";
    inline constexpr const char* Component_getString_Sig = "()Ljava/lang/String;";

    // ─── Extras / Legacy (Added to fix build) ──────────────────────────
    inline constexpr const char* MC_hitResult = "field_1765";
    inline constexpr const char* MC_hitResult_Sig = "Lnet/minecraft/class_239;";
    inline constexpr const char* EntityHitResult_Class = "net/minecraft/class_3966";
    inline constexpr const char* EntityHitResult_getEntity = "method_17782";
    inline constexpr const char* EntityHitResult_getEntity_Sig = "()Lnet/minecraft/class_1297;";
    
    inline constexpr const char* MC_getConnection = "method_1562";
    inline constexpr const char* MC_getConnection_Sig = "()Lnet/minecraft/class_634;";
    inline constexpr const char* ClientCommonPacketListenerImpl_Class = "net/minecraft/class_634";
    inline constexpr const char* CCPLI_connection = "field_45611"; // For 1.21 network handler
    inline constexpr const char* CCPLI_connection_Sig = "Lnet/minecraft/class_2535;";
    inline constexpr const char* Connection_send = "method_10752";
    inline constexpr const char* Connection_send_Sig = "(Lnet/minecraft/class_2596;)V";
    inline constexpr const char* ServerboundMovePlayerPacket_Pos_Class = "net/minecraft/class_2828$class_2829";
    
    inline constexpr const char* Player_swing = "method_6104";
    inline constexpr const char* Player_swing_Sig = "(Lnet/minecraft/class_1268;)V";
    inline constexpr const char* InteractionHand_Class = "net/minecraft/class_1268";
    inline constexpr const char* InteractionHand_MAIN_HAND = "field_5808";
    inline constexpr const char* InteractionHand_MAIN_HAND_Sig = "Lnet/minecraft/class_1268;";

    inline constexpr const char* Block_Class = "net/minecraft/class_2248";
    inline constexpr const char* Block_getDescriptionId = "method_9539";
    inline constexpr const char* Block_getDescriptionId_Sig = "()Ljava/lang/String;";

    inline constexpr const char* Vec3_D_Sig = "D";
    inline constexpr const char* AABB_D_Sig = "D";

    inline constexpr const char* LivingEntity_jumping = "field_6281";
    inline constexpr const char* LivingEntity_jumping_Sig = "Z";
    inline constexpr const char* LivingEntity_discardFriction = "field_6214";
    inline constexpr const char* LivingEntity_discardFriction_Sig = "Z";
    inline constexpr const char* Entity_isShiftKeyDown = "method_5715";
    inline constexpr const char* Entity_isShiftKeyDown_Sig = "()Z";

    inline constexpr const char* GR_getProjectionMatrix = "method_3195";
    inline constexpr const char* GR_getProjectionMatrix_Sig = "(D)Lorg/joml/Matrix4f;";
    inline constexpr const char* RS_getProjectionMatrix = "getProjectionMatrix";
    inline constexpr const char* RS_getProjectionMatrix_Sig = "()Lorg/joml/Matrix4f;";
    inline constexpr const char* RS_getModelViewMatrix = "getModelViewMatrix";
    inline constexpr const char* RS_getModelViewMatrix_Sig = "()Lorg/joml/Matrix4f;";

    inline constexpr const char* Matrix4f_m00 = "m00";
    inline constexpr const char* Matrix4f_m01 = "m01";
    inline constexpr const char* Matrix4f_m02 = "m02";
    inline constexpr const char* Matrix4f_m03 = "m03";
    inline constexpr const char* Matrix4f_m10 = "m10";
    inline constexpr const char* Matrix4f_m11 = "m11";
    inline constexpr const char* Matrix4f_m12 = "m12";
    inline constexpr const char* Matrix4f_m13 = "m13";
    inline constexpr const char* Matrix4f_m20 = "m20";
    inline constexpr const char* Matrix4f_m21 = "m21";
    inline constexpr const char* Matrix4f_m22 = "m22";
    inline constexpr const char* Matrix4f_m23 = "m23";
    inline constexpr const char* Matrix4f_m30 = "m30";
    inline constexpr const char* Matrix4f_m31 = "m31";
    inline constexpr const char* Matrix4f_m32 = "m32";
    inline constexpr const char* Matrix4f_m33 = "m33";

    inline constexpr const char* List_size = "size";
    inline constexpr const char* List_size_Sig = "()I";
    inline constexpr const char* List_get = "get";
    inline constexpr const char* List_get_Sig = "(I)Ljava/lang/Object;";

}
