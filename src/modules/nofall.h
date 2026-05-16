#pragma once
#include "modules/module.h"

class NoFallModule : public Module {
public:
    NoFallModule();
    
    void onEnable() override;
    void onDisable() override;
    void onUpdate(JNIEnv* env) override;
    void onRender() override;

private:
    int m_mode = 0; // 0 = Vanilla, 1 = Catch
};
