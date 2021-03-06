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

struct Collider2DCmp : BECS::Component_t {
    explicit Collider2DCmp(const BECS::entID entityID, const uint32_t s_W, const uint32_t s_H) : Component_t(entityID), 
        p2( static_cast<int64_t>(s_W), static_cast<int64_t>(s_H) ) { }

    fvec2<fint_t<int64_t>> p2 = fvec2<fint_t<int64_t>>( ( 0l ), ( 0l ) ); //mov.coords + p2 = down-right corner
};

}