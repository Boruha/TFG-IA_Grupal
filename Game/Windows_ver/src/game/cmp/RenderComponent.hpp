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
#include <ecs/cmp/Component_t.hpp>

#include <game/utils/Color.hpp>
#include <game/utils/vec2.hpp>

namespace AIP {

struct RenderComponent : BECS::Component_t {
    explicit RenderComponent(const BECS::entID entityID, const uint32_t s_W, const uint32_t s_H, const Color col) 
        : Component_t(entityID), sprite(s_W, s_H), sprite_C(col) { }

    vec2<uint32_t> sprite { 0u, 0u };
    Color sprite_C { Color::Red };
};

}
