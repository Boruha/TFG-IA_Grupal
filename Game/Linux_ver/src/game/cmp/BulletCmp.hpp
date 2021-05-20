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
#include <game/utils/fvec2.hpp>

namespace AIP {

struct BulletCmp : BECS::Component_t {
    explicit BulletCmp(const BECS::entID entityID, const int64_t p_x, const int64_t p_y, BECS::entID eid, int64_t amount) 
    : Component_t(entityID), spawnPos(p_x, p_y), shooter(eid), damage(amount) { }

    fvec2<fint_t<int64_t>> spawnPos { { 0l }, { 0l } }; //posicion ini. 
    BECS::entID            shooter  { 0u };
    int64_t                damage   { 0  }; 
};

}