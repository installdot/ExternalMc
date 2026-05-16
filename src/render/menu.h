#pragma once
#include "pch.h"
#include <map>

/*
 * Menu — Phobia-style ImGui menu for Null Client.
 *
 * Inspired by Ch1nChun/ImGuiMenu-s "menu phobia" design.
 * Split-panel layout: dark sidebar (navigation) + dark content area.
 * Custom animated widgets drawn via ImDrawList (no imgui source mods).
 */
class Menu {
public:
    static void render();
    static void applyTheme();
    static void toggle() { s_visible = !s_visible; }
    static bool isVisible() { return s_visible; }

private:
    // ── Phobia-style Custom Widgets ─────────────────────────────────
    static bool PhobiaTab(const char* icon, const char* label, bool selected, ImVec2 pos);
    static bool PhobiaCheckbox(const char* label, bool* v);
    static bool PhobiaSliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.1f");
    static void PhobiaChildBegin(const char* title, ImVec2 pos, ImVec2 size);
    static void PhobiaChildEnd();

    // ── Layout Sections ─────────────────────────────────────────────
    static void DrawDecoration();
    static void DrawSidebarTabs();
    static void DrawUserInfo();
    static void DrawParticles();

    // ── Tab Content ─────────────────────────────────────────────────
    static void DrawCombatTab();
    static void DrawMovementTab();
    static void DrawVisualsTab();
    static void DrawUtilityTab();
    static void DrawConfigTab();

    // ── Animation Helpers ───────────────────────────────────────────
    static float AnimateFloat(ImGuiID id, float target, float speed);

    // ── State ───────────────────────────────────────────────────────
    static inline bool  s_visible      = false;
    static inline int   s_selectedTab  = 0;
    static inline float s_openAlpha    = 0.0f;
    static inline ImFont* s_boldFont   = nullptr;
    static inline ImFont* s_defaultFont = nullptr;

    // Particle system
    struct Particle {
        ImVec2 pos;
        ImVec2 target;
        float  speed;
        float  radius;
    };
    static inline Particle s_particles[50] = {};
    static inline bool     s_particlesInit = false;

    // Animation state maps
    static inline std::map<ImGuiID, float> s_hoverAnim;
    static inline std::map<ImGuiID, float> s_fillAnim;
    static inline std::map<ImGuiID, float> s_activeAnim;

    // ── Phobia Colors ───────────────────────────────────────────────
    static constexpr ImU32 COL_BG_LEFT      = IM_COL32(32, 32, 32, 255);
    static constexpr ImU32 COL_BG_RIGHT     = IM_COL32(26, 26, 26, 255);
    static constexpr ImU32 COL_BORDER       = IM_COL32(50, 50, 50, 255);
    static constexpr ImU32 COL_TEXT_DIM     = IM_COL32(105, 105, 105, 255);
    static constexpr ImU32 COL_TEXT_BRIGHT  = IM_COL32(255, 255, 255, 255);
    static constexpr ImU32 COL_ACCENT       = IM_COL32(174, 139, 148, 255);
    static constexpr ImU32 COL_CHILD_BG     = IM_COL32(32, 32, 32, 255);
    static constexpr ImU32 COL_CHILD_BORDER = IM_COL32(50, 50, 50, 255);
    static constexpr ImU32 COL_CHECKBOX_BG  = IM_COL32(41, 41, 41, 255);
    static constexpr ImU32 COL_TAB_ACTIVE   = IM_COL32(41, 41, 41, 255);
    static constexpr ImU32 COL_HOVER_BORDER = IM_COL32(75, 75, 75, 255);
    static constexpr ImU32 COL_SLIDER_BG    = IM_COL32(26, 26, 26, 255);
    static constexpr ImU32 COL_PARTICLE     = IM_COL32(174, 139, 148, 128);

    // ── Layout Constants ────────────────────────────────────────────
    static constexpr float MENU_W           = 700.0f;
    static constexpr float MENU_H           = 480.0f;
    static constexpr float SIDEBAR_W        = 145.0f;
    static constexpr float CONTENT_X        = 155.0f;
    static constexpr float TAB_H            = 30.0f;
    static constexpr float TAB_W            = 135.0f;
    static constexpr float CHILD_TITLE_H    = 25.0f;
};
