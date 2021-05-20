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
#include <ecs/utils/Alias.hpp>

#include <vector>

namespace BECS {

struct Entity_t{
    explicit Entity_t();

    void                    addComponent(cmpTypeID cmpType)       noexcept;
    std::vector<cmpTypeID>& getComponentsType()                   noexcept;
    const entID             getID()                         const noexcept;

private:
    inline static entID counterID  { 0u };
    const         entID ent_id     { 0u };

    std::vector<cmpTypeID> cmp_types;
};

} // NS