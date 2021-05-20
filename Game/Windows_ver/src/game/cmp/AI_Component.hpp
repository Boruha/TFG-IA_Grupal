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

#include <game/utils/Patrol_t.hpp>
#include <game/utils/AI_behaviours.hpp>

#include <vector>

namespace AIP {

struct AI_Component : BECS::Component_t {
    explicit AI_Component(BECS::entID eid, Patrol_t::iterator patIt = { }) 
        : Component_t(eid), patrolIt(patIt), target_pos( *patIt ) { }

    Patrol_t::iterator     patrolIt         { };
    AI_behaviour           current_behavior { AI_behaviour::no_b };
    fvec2<fint_t<int64_t>> target_pos       = fvec2<fint_t<int64_t>>( ( 0l ), ( 0l ) );
    BECS::entID            target_ent       { 0u };
};

} //NS