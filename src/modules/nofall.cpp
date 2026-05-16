#include "pch.h"
#include "modules/nofall.h"
#include "core/jvm_wrapper.h"
#include "config/mappings.h"
#include "render/menu.h"

NoFallModule::NoFallModule() : Module("NoFall", "Prevents fall damage", 0x4E) { // 'N' key
}

void NoFallModule::onEnable() {
}

void NoFallModule::onDisable() {
}

void NoFallModule::onUpdate() {
    JNIEnv* env = JvmWrapper::getEnv();
    if (!env) return;

    jclass mcClass = env->FindClass(Mappings::Minecraft_Class);
    if (!mcClass) return;

    jmethodID getInstance = env->GetStaticMethodID(mcClass, Mappings::MC_getInstance, Mappings::MC_getInstance_Sig);
    jobject mc = env->CallStaticObjectMethod(mcClass, getInstance);
    
    if (mc) {
        jfieldID playerField = env->GetFieldID(mcClass, Mappings::MC_player, Mappings::MC_player_Sig);
        jobject player = env->GetObjectField(mc, playerField);
        
        if (player) {
            jclass entityClass = env->FindClass(Mappings::Entity_Class);
            if (entityClass) {
                // fallDistance is field_6017 (float)
                jfieldID fallDistField = env->GetFieldID(entityClass, "field_6017", "F");
                if (fallDistField) {
                    float fallDist = env->GetFloatField(player, fallDistField);
                    
                    if (m_mode == 0) {
                        // Vanilla mode: constantly set fall distance to 0
                        env->SetFloatField(player, fallDistField, 0.0f);
                    } else if (m_mode == 1) {
                        // Catch mode: if fall distance > 2.5, stop the player (set velocity Y to 0)
                        if (fallDist > 2.5f) {
                            jmethodID getVelocity = env->GetMethodID(entityClass, Mappings::Entity_getDeltaMovement, Mappings::Entity_getDeltaMovement_Sig);
                            jobject vec3 = env->CallObjectMethod(player, getVelocity);
                            
                            if (vec3) {
                                jclass vec3Class = env->FindClass(Mappings::Vec3_Class);
                                jfieldID xField = env->GetFieldID(vec3Class, Mappings::Vec3_x, Mappings::Vec3_x_Sig);
                                jfieldID zField = env->GetFieldID(vec3Class, Mappings::Vec3_z, Mappings::Vec3_z_Sig);
                                
                                double currentX = env->GetDoubleField(vec3, xField);
                                double currentZ = env->GetDoubleField(vec3, zField);
                                
                                jmethodID setVelocity = env->GetMethodID(entityClass, Mappings::Entity_setDeltaMovement, "(DDD)V");
                                if (setVelocity) {
                                    // Stop downward movement
                                    env->CallVoidMethod(player, setVelocity, currentX, 0.0, currentZ);
                                }
                                env->SetFloatField(player, fallDistField, 0.0f);
                                
                                env->DeleteLocalRef(vec3Class);
                                env->DeleteLocalRef(vec3);
                            }
                        }
                    }
                }
                env->DeleteLocalRef(entityClass);
            }
            env->DeleteLocalRef(player);
        }
        env->DeleteLocalRef(mc);
    }
    env->DeleteLocalRef(mcClass);
}

void NoFallModule::renderMenu() {
    ImGui::Text("Mode");
    const char* modes[] = { "Vanilla", "Catch" };
    if (ImGui::BeginCombo("##NoFallMode", modes[m_mode])) {
        for (int i = 0; i < 2; i++) {
            bool isSelected = (m_mode == i);
            if (ImGui::Selectable(modes[i], isSelected)) {
                m_mode = i;
            }
            if (isSelected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
}
