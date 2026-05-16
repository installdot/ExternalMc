#include "pch.h"
#include "render/renderer.h"
#include <GL/gl.h>

void Renderer::init(HWND hwnd) {
    if (s_initialized) return;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.IniFilename = nullptr;  // Don't save layout to disk

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplOpenGL3_Init("#version 130");

    setupStyle();
    s_initialized = true;
}

void Renderer::shutdown() {
    if (!s_initialized) return;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    s_initialized = false;
}

void Renderer::beginFrame() {
    // Save OpenGL state before ImGui messes with it
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void Renderer::endFrame() {
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    // Restore OpenGL state
    glPopAttrib();
}

void Renderer::setupStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Phobia-style base settings
    style.WindowRounding    = 10.0f;
    style.FrameRounding     = 3.0f;
    style.GrabRounding      = 3.0f;
    style.PopupRounding     = 5.0f;
    style.ScrollbarRounding = 3.0f;
    style.ScrollbarSize     = 5.0f;
    style.TabRounding       = 4.0f;
    style.WindowPadding     = ImVec2(0, 0);
    style.FramePadding      = ImVec2(1, 0);
    style.ItemSpacing       = ImVec2(8, 4);
    style.WindowBorderSize  = 0.0f;
    style.FrameBorderSize   = 0.0f;
    style.TabBorderSize     = 0.0f;

    // Backgrounds - Phobia dark
    colors[ImGuiCol_WindowBg]         = ImVec4(0.10f, 0.10f, 0.10f, 0.00f);
    colors[ImGuiCol_ChildBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]          = ImVec4(0.13f, 0.13f, 0.13f, 0.95f);

    // Borders
    colors[ImGuiCol_Border]           = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
    colors[ImGuiCol_BorderShadow]     = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Text
    colors[ImGuiCol_Text]             = ImVec4(0.90f, 0.90f, 0.95f, 1.00f);
    colors[ImGuiCol_TextDisabled]     = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);

    // Headers
    colors[ImGuiCol_Header]           = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_HeaderHovered]    = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_HeaderActive]     = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

    // Buttons
    colors[ImGuiCol_Button]           = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_ButtonHovered]    = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ButtonActive]     = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);

    // Frame
    colors[ImGuiCol_FrameBg]          = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]   = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_FrameBgActive]    = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

    // Accent colors (pink-mauve phobia accent)
    colors[ImGuiCol_CheckMark]        = ImVec4(0.68f, 0.55f, 0.58f, 1.00f);
    colors[ImGuiCol_SliderGrab]       = ImVec4(0.68f, 0.55f, 0.58f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.78f, 0.62f, 0.66f, 1.00f);

    // Tabs
    colors[ImGuiCol_Tab]              = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_TabHovered]       = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TabActive]        = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_TabUnfocused]     = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]= ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

    // Title
    colors[ImGuiCol_TitleBg]          = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_TitleBgActive]    = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg]      = ImVec4(0.05f, 0.05f, 0.05f, 0.30f);
    colors[ImGuiCol_ScrollbarGrab]    = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]= ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]= ImVec4(0.45f, 0.45f, 0.45f, 1.00f);

    // Separators
    colors[ImGuiCol_Separator]        = ImVec4(0.20f, 0.20f, 0.20f, 0.80f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    colors[ImGuiCol_SeparatorActive]  = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
}
