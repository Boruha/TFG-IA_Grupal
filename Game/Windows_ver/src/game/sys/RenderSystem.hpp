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
#include <game/cmp/RenderComponent.hpp>
#include <game/utils/fvec2.hpp>
#include <game/utils/vec2.tpp>

#include <engineGL/EngineManager.hpp>

#include <memory>

namespace AIP {

struct MovementComponent;
struct Collider2DCmp;

template <typename Context_t>
struct RenderSystem {
    explicit RenderSystem(const int64_t w, const int64_t h);

    bool update(Context_t& context) noexcept;
    
    bool debug_mode { false };
private:
    vec2<uint32_t> continuousToScreen(const fvec2<fint_t<int64_t>>& cont) noexcept;
    vec2<uint32_t> clipToDraw(fvec2<fint_t<int64_t>> point)               noexcept;
    
    void drawFacing(const MovementComponent& mov, const RenderComponent& render, vec2<uint32_t>& camScreenCoords) noexcept;
    void drawInterface(Context_t& context) noexcept;
    void draw_debug(MovementComponent& mov, const RenderComponent& render, const Collider2DCmp& coll2D, vec2<uint32_t>& camScreenCoords) noexcept;

    std::unique_ptr<eGL::EngineManager> engine { nullptr };
};

}
