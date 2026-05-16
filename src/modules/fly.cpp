#include "pch.h"
#include "modules/fly.h"
#include "core/jvm_wrapper.h"
#include "config/mappings.h"
#include "render/menu.h"

FlyModule::FlyModule() : Module("Fly", 0x46) { // 'F' key
}

void FlyModule::onEnable() {
}

void FlyModule::onDisable() {
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
            jclass playerClass = env->FindClass(Mappings::Player_Class);
            if (playerClass) {
                jfieldID abilitiesField = env->GetFieldID(playerClass, Mappings::Player_abilities, Mappings::Player_abilities_Sig);
                jobject abilities = env->GetObjectField(player, abilitiesField);
                
                if (abilities) {
                    jclass abilitiesClass = env->GetObjectClass(abilities);
                    jfieldID flyingField = env->GetFieldID(abilitiesClass, Mappings::PlayerAbilities_flying, Mappings::PlayerAbilities_flying_Sig);
                    env->SetBooleanField(abilities, flyingField, JNI_FALSE);
                    
                    env->DeleteLocalRef(abilitiesClass);
                    env->DeleteLocalRef(abilities);
                }
                env->DeleteLocalRef(playerClass);
            }
            env->DeleteLocalRef(player);
        }
        env->DeleteLocalRef(mc);
    }
    env->DeleteLocalRef(mcClass);
}

void FlyModule::onUpdate(JNIEnv* env) {
    if (!env) return;

    jclass mcClass = env->FindClass(Mappings::Minecraft_Class);
    if (!mcClass) return;

    jmethodID getInstance = env->GetStaticMethodID(mcClass, Mappings::MC_getInstance, Mappings::MC_getInstance_Sig);
    jobject mc = env->CallStaticObjectMethod(mcClass, getInstance);
    
    if (mc) {
        jfieldID playerField = env->GetFieldID(mcClass, Mappings::MC_player, Mappings::MC_player_Sig);
        jobject player = env->GetObjectField(mc, playerField);
        
        if (player) {
            if (m_mode == 0) {
                // Vanilla Fly
                jclass playerClass = env->FindClass(Mappings::Player_Class);
                if (playerClass) {
                    jfieldID abilitiesField = env->GetFieldID(playerClass, Mappings::Player_abilities, Mappings::Player_abilities_Sig);
                    jobject abilities = env->GetObjectField(player, abilitiesField);
                    
                    if (abilities) {
                        jclass abilitiesClass = env->GetObjectClass(abilities);
                        jfieldID flyingField = env->GetFieldID(abilitiesClass, Mappings::PlayerAbilities_flying, Mappings::PlayerAbilities_flying_Sig);
                        env->SetBooleanField(abilities, flyingField, JNI_TRUE);
                        
                        env->DeleteLocalRef(abilitiesClass);
                        env->DeleteLocalRef(abilities);
                    }
                    env->DeleteLocalRef(playerClass);
                }
            } else if (m_mode == 1) {
                // Velocity Fly
                jclass entityClass = env->FindClass(Mappings::Entity_Class);
                if (entityClass) {
                    jmethodID getVelocity = env->GetMethodID(entityClass, Mappings::Entity_getDeltaMovement, Mappings::Entity_getDeltaMovement_Sig);
                    jobject vec3 = env->CallObjectMethod(player, getVelocity);
                    
                    if (vec3) {
                        jclass vec3Class = env->FindClass(Mappings::Vec3_Class);
                        jfieldID xField = env->GetFieldID(vec3Class, Mappings::Vec3_x, Mappings::Vec3_x_Sig);
                        jfieldID zField = env->GetFieldID(vec3Class, Mappings::Vec3_z, Mappings::Vec3_z_Sig);
                        
                        double currentX = env->GetDoubleField(vec3, xField);
                        double currentZ = env->GetDoubleField(vec3, zField);
                        
                        // Force Y velocity upwards (or hold steady)
                        jmethodID setVelocity = env->GetMethodID(entityClass, Mappings::Entity_setDeltaMovement, "(DDD)V");
                        if (setVelocity) {
                            // If user wants this to respond to spacebar, we'd need to read Options.
                            // For simplicity of this velocity fly, we just set Y velocity to 0 or push up slightly
                            env->CallVoidMethod(player, setVelocity, currentX, 0.0, currentZ);
                        }
                        
                        env->DeleteLocalRef(vec3Class);
                        env->DeleteLocalRef(vec3);
                    }
                    env->DeleteLocalRef(entityClass);
                }
            }
            env->DeleteLocalRef(player);
        }
        env->DeleteLocalRef(mc);
    }
    env->DeleteLocalRef(mcClass);
}

void FlyModule::onRender() {
    ImGui::Text("Mode");
    const char* modes[] = { "Vanilla", "Velocity" };
    if (ImGui::BeginCombo("##FlyMode", modes[m_mode])) {
        for (int i = 0; i < 2; i++) {
            bool isSelected = (m_mode == i);
            if (ImGui::Selectable(modes[i], isSelected)) {
                m_mode = i;
            }
            if (isSelected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    
    Menu::PhobiaSliderFloat("Speed", &m_speed, 0.1f, 10.0f, "%.1f");
}
