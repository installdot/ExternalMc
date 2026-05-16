#pragma once
#include "modules/module.h"

class FlyModule : public Module {
public:
    FlyModule();
    
    void onEnable() override;
    void onDisable() override;
    void onUpdate(JNIEnv* env) override;
    void onRender() override;

private:
    int m_mode = 0; // 0 = Vanilla, 1 = Velocity
    float m_speed = 1.0f;
};
