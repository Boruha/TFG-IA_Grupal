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

#include <ecs/utils/Alias.hpp>

namespace BECS {

struct Component_t {
    explicit Component_t(const entID entityID) : cmp_id(++counterID), ent_id(entityID) { }

    [[nodiscard]] cmpID getComponentID() const { return cmp_id; }
    [[nodiscard]] entID getEntityID()    const { return ent_id; }

    template<typename T>
    static cmpTypeID getCmpTypeID() { 
        static const cmpTypeID type_id { ++counterTypeID };
        return  type_id;
    }

private:
    inline static cmpID     counterID     { 0u };
    inline static cmpTypeID counterTypeID { 0u };
                  cmpID     cmp_id        { 0u };
                  entID     ent_id        { 0u };
};

}
