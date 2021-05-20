/*
Copyright (C) <2020-2021> Borja Pozo Wals (Tw: @Chico_Riot | GitHub: Boruha)

This file is part of 'TFG: Gestión y manejo de comportamientos grupales 
de entidades en videojuegos'.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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

    void drawRect(      uint32_t pos_x, uint32_t pos_y, uint32_t size_x, uint32_t size_y, uint32_t color, bool filled) noexcept;
    void drawInMinimap( uint32_t pos_x, uint32_t pos_y, uint32_t size_x, uint32_t size_y, uint32_t color, bool filled) noexcept;
    void drawLine(      uint32_t p1_x , uint32_t p1_y , uint32_t p2_x  , uint32_t p2_y  , uint32_t color)              noexcept;
    void drawMsg(       uint32_t p1_x , uint32_t p1_y , uint32_t size_x, uint32_t size_y, const char* text)            noexcept;

    void debugInterface(bool& showDebug, float& DT, float& LT, bool& changed) const noexcept;

    void modeInterface(unsigned int& opc, unsigned int& frm) const noexcept;

    void minimap()     noexcept;
    void render()      noexcept;
    void start_frame() noexcept;
    bool shouldClose() noexcept;

    void setMiniMapFraction(int64_t world_x, int64_t world_y) noexcept;
    
    constexpr const std::tuple<int, int> getWindowSize() const noexcept;

private:
    GLFWwindow* window { nullptr };
    
    float red     { 0.f };
    float green   { 0.f };
    float blue    { 0.f };
    float alpha   { 1.f };
    
    int display_w { 0 };
    int display_h { 0 };
    
    ImVec2 fraction { 0.f, 0.f };
};

} //NS