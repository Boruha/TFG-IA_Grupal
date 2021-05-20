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

#include <game/sys/AttackSystem.hpp>
#include <game/cmp/CombatComponent.hpp>
#include <game/cmp/EventCmp_t.hpp>

#include <ecs/ent/Entity_t.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

template <typename Context_t>
void 
AttackSystem<Context_t>::update(Context_t& context) noexcept {
    auto& eventCmp = context.template getSCmpByType<EventCmp_t>();
    auto& atk_vec  = eventCmp.attack_msg;
    
    std::for_each(atk_vec.rbegin(), atk_vec.rend(), [&](auto& msg) {
            auto& combat_cmp   = context.template getCmpByEntityID<CombatComponent>( msg.eid_damaged );
            combat_cmp.health -= msg.amount;

            if(combat_cmp.health <= 0)
                eventCmp.death_msg.emplace(msg.eid_damaged, EntType::Human);

            atk_vec.pop_back();
    });
}

} // NS