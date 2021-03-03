#pragma once
#include "imgui/imgui.hpp"
#include "backends/imgui_impl_glfw.hpp"
#include "backends/imgui_impl_opengl3.hpp"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <tuple>

namespace eGL {

struct EngineManager {
    EngineManager(int win_w, int win_h, const char* name);
   ~EngineManager();

    EngineManager(const EngineManager& )            = delete;
    EngineManager(const EngineManager&&)            = delete;
    EngineManager& operator=(const EngineManager& ) = delete;
    EngineManager& operator=(const EngineManager&&) = delete;

    void drawRectFilled(uint32_t pos_x, uint32_t pos_y, uint32_t size_x, uint32_t size_y, uint32_t color) noexcept;
    void drawLine(uint32_t p1_x, uint32_t p1_y, uint32_t p2_x, uint32_t p2_y, uint32_t color)             noexcept;
    
    void render()      noexcept;
    void start_frame() noexcept;
    bool shouldClose() noexcept;
    
    constexpr const std::tuple<int, int> getWindowSize() const noexcept;

private:
    GLFWwindow* window { nullptr };
    
    float red     { 0.f };
    float green   { 0.f };
    float blue    { 0.f };
    float alpha   { 1.f };
    int display_w { 0 };
    int display_h { 0 };
};

} //NS