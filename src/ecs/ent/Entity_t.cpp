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

#include <ecs/ent/Entity_t.hpp>

namespace BECS {

Entity_t::Entity_t() : ent_id(++counterID) { }

void 
Entity_t::addComponent(cmpTypeID cmpType) noexcept {
    cmp_types.emplace_back(cmpType);
}

std::vector<cmpTypeID>&
Entity_t::getComponentsType() noexcept { 
    return cmp_types; 
}

const entID
Entity_t::getID() const noexcept { 
    return ent_id; 
}


} //NS