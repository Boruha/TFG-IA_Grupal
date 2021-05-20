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
#include <game/utils/fint_t.hpp>

namespace AIP {

/*  World  = cont.  = fint_t; -> MovementComponent.pos
    Camera = cont.  = fint_t; -> CamSystem = MovementComponent.pos - Cam.MovementComponent.pos
    Screen = pixels = uint_t; -> contToScreen( CamSystem )
*/

//Screen Settings to setup window render->engine. Range -> X:[0 - Win_W] / Y:[0 - Win_H]
constexpr uint32_t UWIN_W { 1920u };
constexpr uint32_t UWIN_H { 1080u };

constexpr int64_t WIN_W { static_cast<int64_t>(UWIN_W) };
constexpr int64_t WIN_H { static_cast<int64_t>(UWIN_H) };

constexpr int64_t HALF_WIN_W { WIN_W/2 };
constexpr int64_t HALF_WIN_H { WIN_H/2 };

//World coords to setup level limits. Range -> X:[0 - World_W] / Y:[0 - World_H]
constexpr int64_t WORLD_W { WIN_W * 2 }; //WIN_W + HALF_WIN_W
constexpr int64_t WORLD_H { WIN_H * 2 }; //WIN_H + HALF_WIN_H

constexpr int64_t HALF_WORLD_W { WORLD_W/2 };
constexpr int64_t HALF_WORLD_H { WORLD_H/2 };

constexpr fint_t FIXED_HALF_WORLD_W { HALF_WORLD_W };
constexpr fint_t FIXED_HALF_WORLD_H { HALF_WORLD_H };

constexpr fint_t FIXED_HALF_WORLD_W_N { HALF_WORLD_W * -1 };
constexpr fint_t FIXED_HALF_WORLD_H_N { HALF_WORLD_H * -1 };

}