#include "pch.h"
#include "render/menu.h"
#include "modules/module_manager.h"
#include "core/jvm_wrapper.h"
#include "config/mappings.h"
#include <map>
#include <cstdlib>
#include <imgui_internal.h>

// ── Animation Helper ────────────────────────────────────────────────
float Menu::AnimateFloat(ImGuiID id, float target, float speed) {
    auto it = s_fillAnim.find(id);
    if (it == s_fillAnim.end()) { s_fillAnim[id] = target; return target; }
    it->second = it->second + (target - it->second) * ImMin(speed * ImGui::GetIO().DeltaTime, 1.0f);
    return it->second;
}

// ── Phobia Tab ──────────────────────────────────────────────────────
bool Menu::PhobiaTab(const char* icon, const char* label, bool selected, ImVec2 pos) {
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    ImGuiID id = window->GetID(label);
    ImVec2 size(TAB_W, TAB_H);
    ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));

    ImGui::SetCursorScreenPos(pos);
    bool pressed = ImGui::InvisibleButton(label, size);

    bool hovered = ImGui::IsItemHovered();
    float hoverA = AnimateFloat(id + 1000, hovered ? 1.0f : 0.0f, 8.0f);
    float selA   = AnimateFloat(id + 2000, selected ? 1.0f : 0.0f, 8.0f);
    float alpha  = ImGui::GetStyle().Alpha;
    auto* dl     = ImGui::GetWindowDrawList();

    // Selected background
    if (selA > 0.01f)
        dl->AddRectFilled(bb.Min, bb.Max, IM_COL32(41, 41, 41, (int)(255 * selA * alpha)), 5.0f);

    // Accent bar on left when selected
    if (selA > 0.01f)
        dl->AddRectFilled(ImVec2(bb.Min.x, bb.Min.y + 5), ImVec2(bb.Min.x + selA * 3, bb.Min.y + 25),
                          IM_COL32(174, 139, 148, (int)(255 * alpha)), 10.0f);

    // Hover outline
    if (hoverA > 0.01f)
        dl->AddRect(bb.Min, bb.Max, IM_COL32(75, 75, 75, (int)(255 * hoverA * alpha)), 5.0f);

    // Icon + Label (dim base, bright when selected/hovered)
    float textA = 0.25f + 0.75f * ImMax(selA, hoverA * 0.5f);
    ImU32 textCol = IM_COL32(255, 255, 255, (int)(255 * textA * alpha));
    if (s_boldFont) ImGui::PushFont(s_boldFont);
    dl->AddText(ImVec2(bb.Min.x + 12, bb.Min.y + 7), textCol, icon);
    if (s_boldFont) ImGui::PopFont();
    dl->AddText(ImVec2(bb.Min.x + 35, bb.Min.y + 8), textCol, label);

    return pressed;
}

// ── Phobia Checkbox ─────────────────────────────────────────────────
bool Menu::PhobiaCheckbox(const char* label, bool* v) {
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    ImGuiID id = window->GetID(label);
    float alpha = ImGui::GetStyle().Alpha;
    auto* dl = ImGui::GetWindowDrawList();

    ImVec2 cursor = ImGui::GetCursorScreenPos();
    float boxSz = 18.0f;
    ImVec2 totalSize(ImGui::GetContentRegionAvail().x, boxSz + 4);
    ImGui::SetCursorScreenPos(cursor);
    bool pressed = ImGui::InvisibleButton(label, totalSize);
    if (pressed) *v = !(*v);

    bool hovered = ImGui::IsItemHovered();
    float hoverA = AnimateFloat(id + 3000, hovered ? 1.0f : 0.0f, 8.0f);
    float checkA = AnimateFloat(id + 4000, *v ? 1.0f : 0.0f, 10.0f);

    ImVec2 boxMin(cursor.x, cursor.y + 2);
    ImVec2 boxMax(cursor.x + boxSz, cursor.y + 2 + boxSz);

    // Box border
    dl->AddRect(boxMin, boxMax, IM_COL32(41, 41, 41, (int)(255 * alpha)), 3.0f);
    if (hoverA > 0.01f)
        dl->AddRect(boxMin, boxMax, IM_COL32(75, 75, 75, (int)(255 * hoverA * alpha)), 3.0f);

    // Checkmark
    if (checkA > 0.01f) {
        float pad = 4.0f;
        ImVec2 a(boxMin.x + pad, boxMin.y + boxSz * 0.5f);
        ImVec2 b(boxMin.x + boxSz * 0.4f, boxMax.y - pad);
        ImVec2 c(boxMax.x - pad, boxMin.y + pad);
        dl->AddLine(a, b, IM_COL32(174, 139, 148, (int)(255 * checkA * alpha)), 2.0f);
        dl->AddLine(b, c, IM_COL32(174, 139, 148, (int)(255 * checkA * alpha)), 2.0f);
    }

    // Label text
    float textBright = 0.41f + 0.59f * ImMax(hoverA * 0.6f, *v ? 1.0f : 0.0f);
    dl->AddText(ImVec2(cursor.x + boxSz + 8, cursor.y + 2),
                IM_COL32(255, 255, 255, (int)(255 * textBright * alpha)), label);

    return pressed;
}

// ── Phobia Slider ───────────────────────────────────────────────────
bool Menu::PhobiaSliderFloat(const char* label, float* v, float v_min, float v_max, const char* format) {
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    ImGuiID id = window->GetID(label);
    float alpha = ImGui::GetStyle().Alpha;
    auto* dl = ImGui::GetWindowDrawList();

    float availW = ImGui::GetContentRegionAvail().x;
    ImVec2 cursor = ImGui::GetCursorScreenPos();

    // Label above
    dl->AddText(ImVec2(cursor.x, cursor.y), IM_COL32(255, 255, 255, (int)(200 * alpha)), label);

    // Value text on right
    char valBuf[32];
    snprintf(valBuf, sizeof(valBuf), format, *v);
    ImVec2 valSz = ImGui::CalcTextSize(valBuf);
    dl->AddText(ImVec2(cursor.x + availW - valSz.x, cursor.y),
                IM_COL32(255, 255, 255, (int)(200 * alpha)), valBuf);

    // Slider bar area
    float barY = cursor.y + 20;
    float barH = 8.0f;
    ImVec2 barMin(cursor.x, barY);
    ImVec2 barMax(cursor.x + availW, barY + barH);

    ImGui::SetCursorScreenPos(barMin);
    ImGui::InvisibleButton(label, ImVec2(availW, barH + 10));

    bool hovered = ImGui::IsItemHovered();
    bool active = ImGui::IsItemActive();
    if (active) {
        float mouseX = ImGui::GetIO().MousePos.x;
        float t = ImClamp((mouseX - barMin.x) / availW, 0.0f, 1.0f);
        *v = v_min + t * (v_max - v_min);
    }

    float hoverA = AnimateFloat(id + 5000, hovered || active ? 1.0f : 0.0f, 8.0f);
    float frac = (*v - v_min) / (v_max - v_min);

    // Background bar
    dl->AddRectFilled(barMin, barMax, IM_COL32(26, 26, 26, (int)(255 * alpha)), 3.0f);
    dl->AddRect(barMin, barMax, IM_COL32(50, 50, 50, (int)(255 * alpha)), 3.0f);
    if (hoverA > 0.01f)
        dl->AddRect(barMin, barMax, IM_COL32(75, 75, 75, (int)(255 * hoverA * alpha)), 3.0f);

    // Filled portion
    if (frac > 0.001f)
        dl->AddRectFilled(barMin, ImVec2(barMin.x + availW * frac, barMax.y), 
                          IM_COL32(174, 139, 148, (int)(255 * alpha)), 3.0f);

    ImGui::SetCursorScreenPos(ImVec2(cursor.x, barY + barH + 6));
    return active;
}

// ── Phobia Child Panel ──────────────────────────────────────────────
void Menu::PhobiaChildBegin(const char* title, ImVec2 pos, ImVec2 size) {
    auto* dl = ImGui::GetWindowDrawList();
    float alpha = ImGui::GetStyle().Alpha;

    dl->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y),
                      IM_COL32(32, 32, 32, (int)(255 * alpha)), 5.0f);
    dl->AddRect(pos, ImVec2(pos.x + size.x, pos.y + size.y),
                IM_COL32(50, 50, 50, (int)(255 * alpha)), 5.0f);

    if (s_boldFont) ImGui::PushFont(s_boldFont);
    dl->AddText(ImVec2(pos.x + 10, pos.y + 6),
                IM_COL32(105, 105, 105, (int)(255 * alpha)), title);
    if (s_boldFont) ImGui::PopFont();

    ImGui::SetCursorScreenPos(ImVec2(pos.x + 10, pos.y + CHILD_TITLE_H + 4));
    ImGui::BeginGroup();
    ImGui::PushItemWidth(size.x - 30);
}

void Menu::PhobiaChildEnd() {
    ImGui::PopItemWidth();
    ImGui::EndGroup();
}

// ── Decoration (backgrounds) ────────────────────────────────────────
void Menu::DrawDecoration() {
    auto* dl = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetWindowPos();
    float alpha = ImGui::GetStyle().Alpha;

    // Left sidebar
    dl->AddRectFilled(pos, ImVec2(pos.x + SIDEBAR_W, pos.y + MENU_H),
                      IM_COL32(32, 32, 32, (int)(255 * alpha)), 10.0f, ImDrawFlags_RoundCornersLeft);
    dl->AddRect(pos, ImVec2(pos.x + SIDEBAR_W, pos.y + MENU_H),
                IM_COL32(50, 50, 50, (int)(255 * alpha)), 10.0f, ImDrawFlags_RoundCornersLeft);

    // Right content area
    dl->AddRectFilled(ImVec2(pos.x + SIDEBAR_W - 1, pos.y), ImVec2(pos.x + MENU_W, pos.y + MENU_H),
                      IM_COL32(26, 26, 26, (int)(255 * alpha)), 10.0f, ImDrawFlags_RoundCornersRight);
    dl->AddRect(ImVec2(pos.x + SIDEBAR_W - 1, pos.y), ImVec2(pos.x + MENU_W, pos.y + MENU_H),
                IM_COL32(50, 50, 50, (int)(255 * alpha)), 10.0f, ImDrawFlags_RoundCornersRight);

    // Title text in sidebar
    if (s_boldFont) ImGui::PushFont(s_boldFont);
    dl->AddText(ImVec2(pos.x + 20, pos.y + 20),
                IM_COL32(255, 255, 255, (int)(220 * alpha)), "NULL CLIENT");
    if (s_boldFont) ImGui::PopFont();
    dl->AddText(ImVec2(pos.x + 20, pos.y + 42),
                IM_COL32(105, 105, 105, (int)(255 * alpha)), "Fabric 1.21");
}

// ── Sidebar Tabs ────────────────────────────────────────────────────
void Menu::DrawSidebarTabs() {
    ImVec2 pos = ImGui::GetWindowPos();
    auto* dl = ImGui::GetWindowDrawList();
    float alpha = ImGui::GetStyle().Alpha;

    // Section headers
    dl->AddText(ImVec2(pos.x + 13, pos.y + 68),
                IM_COL32(105, 105, 105, (int)(200 * alpha)), "Modules");

    float startY = 88.0f;
    struct TabDef { const char* icon; const char* label; };
    TabDef tabs[] = {
        {">>", "Combat"},
        {"~~", "Movement"},
        {"()", "Visuals"},
        {"[]", "Utility"},
    };

    for (int i = 0; i < 4; i++) {
        ImVec2 tabPos(pos.x + 13, pos.y + startY + i * 38);
        if (PhobiaTab(tabs[i].icon, tabs[i].label, s_selectedTab == i, tabPos))
            s_selectedTab = i;
    }

    // Settings section header
    dl->AddText(ImVec2(pos.x + 13, pos.y + startY + 4 * 38 + 10),
                IM_COL32(105, 105, 105, (int)(200 * alpha)), "Settings");
    ImVec2 cfgPos(pos.x + 13, pos.y + startY + 4 * 38 + 28);
    if (PhobiaTab("##", "Configs", s_selectedTab == 4, cfgPos))
        s_selectedTab = 4;
}

// ── User Info ───────────────────────────────────────────────────────
void Menu::DrawUserInfo() {
    auto* dl = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetWindowPos();
    float alpha = ImGui::GetStyle().Alpha;

    ImVec2 boxMin(pos.x + 9, pos.y + MENU_H - 50);
    ImVec2 boxMax(pos.x + SIDEBAR_W - 9, pos.y + MENU_H - 12);
    dl->AddRectFilled(boxMin, boxMax, IM_COL32(41, 41, 41, (int)(255 * alpha)), 5.0f);
    dl->AddRect(boxMin, boxMax, IM_COL32(50, 50, 50, (int)(255 * alpha)), 5.0f);

    dl->AddText(ImVec2(boxMin.x + 10, boxMin.y + 5),
                IM_COL32(255, 255, 255, (int)(200 * alpha)), "Player");
    dl->AddText(ImVec2(boxMin.x + 10, boxMin.y + 20),
                IM_COL32(105, 105, 105, (int)(200 * alpha)), "v2.6 Premium");
}

// ── Particles ───────────────────────────────────────────────────────
void Menu::DrawParticles() {
    ImVec2 wPos = ImGui::GetWindowPos();
    float alpha = ImGui::GetStyle().Alpha;
    auto* dl = ImGui::GetWindowDrawList();

    if (!s_particlesInit) {
        for (int i = 0; i < 50; i++) {
            s_particles[i].pos = ImVec2((float)(rand() % (int)MENU_W), 0.0f);
            s_particles[i].target = ImVec2((float)(rand() % (int)MENU_W), MENU_H * 2);
            s_particles[i].speed = 1.0f + (rand() % 25);
            s_particles[i].radius = (float)(rand() % 3 + 1);
        }
        s_particlesInit = true;
    }

    float dt = ImGui::GetIO().DeltaTime;
    for (int i = 0; i < 50; i++) {
        auto& p = s_particles[i];
        float lerpSpeed = dt * (p.speed / 60.0f);
        p.pos.x += (p.target.x - p.pos.x) * lerpSpeed;
        p.pos.y += (p.target.y - p.pos.y) * lerpSpeed;

        if (p.pos.y > MENU_H) {
            p.pos = ImVec2((float)(rand() % (int)MENU_W), 0.0f);
            p.target = ImVec2((float)(rand() % (int)MENU_W), MENU_H * 2);
            p.speed = 1.0f + (rand() % 25);
        }

        dl->AddCircleFilled(ImVec2(wPos.x + p.pos.x, wPos.y + p.pos.y),
                            p.radius, IM_COL32(174, 139, 148, (int)(128 * alpha)));
    }
}

// ── Tab Content: Combat ─────────────────────────────────────────────
void Menu::DrawCombatTab() {
    ImVec2 wPos = ImGui::GetWindowPos();
    float colW = 310.0f;

    // Left column - General
    PhobiaChildBegin("General", ImVec2(wPos.x + CONTENT_X, wPos.y + 38), ImVec2(colW, 240));
    {
        auto* reach = ModuleManager::getModule("Reach");
        if (reach) {
            bool en = reach->isEnabled();
            PhobiaCheckbox("Reach Extension", &en);
            reach->setEnabled(en);
            if (en) PhobiaSliderFloat("Max Distance", &reach->getFloatSetting("reach_distance"), 3.0f, 10.0f, "%.1f");
        }
        ImGui::Spacing();
        auto* aim = ModuleManager::getModule("Aim Assist");
        if (aim) {
            bool en = aim->isEnabled();
            PhobiaCheckbox("Aim Assist", &en);
            aim->setEnabled(en);
            if (en) {
                PhobiaCheckbox("Interpolation", &aim->getBoolSetting("aim_assist"));
                PhobiaSliderFloat("FOV Radius", &aim->getFloatSetting("aim_fov"), 10.0f, 180.0f, "%.0f");
                PhobiaSliderFloat("Smoothness", &aim->getFloatSetting("aim_speed"), 0.1f, 5.0f, "%.1f");
            }
        }
    }
    PhobiaChildEnd();

    // Right column - Extras
    PhobiaChildBegin("Extras", ImVec2(wPos.x + CONTENT_X + colW + 10, wPos.y + 38), ImVec2(colW, 240));
    {
        auto* aim = ModuleManager::getModule("Aim Assist");
        if (aim) {
            PhobiaCheckbox("Triggerbot", &aim->getBoolSetting("triggerbot"));
            PhobiaCheckbox("AutoClicker", &aim->getBoolSetting("auto_clicker"));
            PhobiaSliderFloat("CPS Max", &aim->getFloatSetting("cps"), 1.0f, 20.0f, "%.0f");
        }
    }
    PhobiaChildEnd();
}

// ── Tab Content: Movement ───────────────────────────────────────────
void Menu::DrawMovementTab() {
    ImVec2 wPos = ImGui::GetWindowPos();

    PhobiaChildBegin("Movement", ImVec2(wPos.x + CONTENT_X, wPos.y + 38), ImVec2(310, 200));
    {
        auto* jesus = ModuleManager::getModule("Jesus");
        if (jesus) {
            bool en = jesus->isEnabled();
            PhobiaCheckbox("Water Walking", &en);
            jesus->setEnabled(en);
            if (en) {
                PhobiaCheckbox("Solid Collision", &jesus->getBoolSetting("solid"));
                PhobiaSliderFloat("Surface Bounce", &jesus->getFloatSetting("bounce"), 0.0f, 0.4f, "%.2f");
            }
        }
    }
    PhobiaChildEnd();
}

// ── Tab Content: Visuals ────────────────────────────────────────────
void Menu::DrawVisualsTab() {
    ImVec2 wPos = ImGui::GetWindowPos();
    float colW = 310.0f;

    PhobiaChildBegin("ESP Options", ImVec2(wPos.x + CONTENT_X, wPos.y + 38), ImVec2(colW, 340));
    {
        auto* esp = ModuleManager::getModule("ESP");
        if (esp) {
            bool en = esp->isEnabled();
            PhobiaCheckbox("Master Overlay", &en);
            esp->setEnabled(en);
            if (en) {
                PhobiaCheckbox("2D Bounding Boxes", &esp->getBoolSetting("draw_boxes"));
                PhobiaCheckbox("Render Names", &esp->getBoolSetting("draw_names"));
                PhobiaCheckbox("Health Bars", &esp->getBoolSetting("draw_health"));
                PhobiaCheckbox("Distance Info", &esp->getBoolSetting("draw_distance"));
                PhobiaCheckbox("Skeleton Chams", &esp->getBoolSetting("chams"));
                PhobiaCheckbox("Render Animals", &esp->getBoolSetting("draw_animals"));
                PhobiaCheckbox("Dropped Items", &esp->getBoolSetting("draw_items"));
                PhobiaSliderFloat("Visual Range", &esp->getFloatSetting("max_distance"), 10.0f, 500.0f, "%.0fm");
            }
        }
    }
    PhobiaChildEnd();
}

// ── Tab Content: Utility ────────────────────────────────────────────
void Menu::DrawUtilityTab() {
    ImVec2 wPos = ImGui::GetWindowPos();
    float colW = 310.0f;

    PhobiaChildBegin("X-Ray Scanner", ImVec2(wPos.x + CONTENT_X, wPos.y + 38), ImVec2(colW, 340));
    {
        auto* xray = ModuleManager::getModule("X-Ray");
        if (xray) {
            bool en = xray->isEnabled();
            PhobiaCheckbox("Enable X-Ray", &en);
            xray->setEnabled(en);
            if (en) {
                PhobiaCheckbox("Diamond", &xray->getBoolSetting("diamond"));
                PhobiaCheckbox("Iron", &xray->getBoolSetting("iron"));
                PhobiaCheckbox("Gold", &xray->getBoolSetting("gold"));
                PhobiaCheckbox("Emerald", &xray->getBoolSetting("emerald"));
                PhobiaCheckbox("Coal", &xray->getBoolSetting("coal"));
                PhobiaCheckbox("Lapis", &xray->getBoolSetting("lapis"));
                PhobiaCheckbox("Redstone", &xray->getBoolSetting("redstone"));
                PhobiaCheckbox("Spawners", &xray->getBoolSetting("spawner"));
                PhobiaSliderFloat("Search Radius", &xray->getFloatSetting("radius"), 10.0f, 100.0f, "%.0f");
                PhobiaSliderFloat("Tracer Width", &xray->getFloatSetting("thickness"), 1.0f, 5.0f, "%.1f");
            }
        }
    }
    PhobiaChildEnd();
}

// ── Tab Content: Config ─────────────────────────────────────────────
void Menu::DrawConfigTab() {
    ImVec2 wPos = ImGui::GetWindowPos();
    PhobiaChildBegin("Configuration", ImVec2(wPos.x + CONTENT_X, wPos.y + 38), ImVec2(310, 120));
    {
        auto* dl = ImGui::GetWindowDrawList();
        float alpha = ImGui::GetStyle().Alpha;
        dl->AddText(ImGui::GetCursorScreenPos(), IM_COL32(105,105,105,(int)(255*alpha)), 
                    "Config save/load coming soon.");
    }
    PhobiaChildEnd();
}

// ── Theme Setup ─────────────────────────────────────────────────────
void Menu::applyTheme() {
    auto& io = ImGui::GetIO();
    if (s_boldFont == nullptr) {
        s_boldFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arialbd.ttf", 16.0f);
        if (!s_boldFont)
            s_boldFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 16.0f);
    }
}

// ── Main Render ─────────────────────────────────────────────────────
void Menu::render() {
    if (!s_visible && s_openAlpha <= 0.01f) return;

    // Fade animation
    float targetAlpha = s_visible ? 1.0f : 0.0f;
    s_openAlpha += (targetAlpha - s_openAlpha) * ImMin(8.0f * ImGui::GetIO().DeltaTime, 1.0f);
    if (s_openAlpha <= 0.01f) return;

    static bool themeApplied = false;
    if (!themeApplied) { applyTheme(); themeApplied = true; }

    ImGui::SetNextWindowSize(ImVec2(MENU_W, MENU_H));
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, s_openAlpha);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));

    ImGui::Begin("##NullClient", nullptr,
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);
    {
        DrawDecoration();
        DrawSidebarTabs();
        DrawUserInfo();
        DrawParticles();

        switch (s_selectedTab) {
            case 0: DrawCombatTab(); break;
            case 1: DrawMovementTab(); break;
            case 2: DrawVisualsTab(); break;
            case 3: DrawUtilityTab(); break;
            case 4: DrawConfigTab(); break;
        }
    }
    ImGui::End();

    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar(2);
}
