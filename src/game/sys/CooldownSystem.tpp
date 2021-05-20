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

#include <game/sys/CooldownSystem.hpp>
#include <game/cmp/CombatComponent.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

template <typename Context_t>
void 
CooldownSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {
    auto& combatCmps = context.template getComponentVector<CombatComponent>();

    std::for_each(begin(combatCmps), end(combatCmps), [&DeltaTime](CombatComponent& combat) {
        if(combat.current_attack_cd > 0)
            combat.current_attack_cd -= DeltaTime;
    });

    auto& bb = context.template getSCmpByType<BlackBoardCmp>();
    if(bb.current_reaction_cd.number > 0)
            bb.current_reaction_cd -= DeltaTime;
}

} // NS