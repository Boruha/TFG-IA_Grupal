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
#include <game/cmp/CmpIncludeList.hpp>
#include <ecs/utils/Alias.hpp>

#include <vector>
#include <optional>

namespace BECS {

struct CmpCollection {
    virtual      ~CmpCollection()                        = default;
    virtual bool deleteCmpByEntityID(entID eid) noexcept = 0;
};

template<typename T>
struct CmpVector : CmpCollection {
    explicit CmpVector();
    bool     deleteCmpByEntityID(entID eid) noexcept override;
    auto     findCmpByEntityID(entID eid)   noexcept;

    static const std::size_t    MAX_CMP_SIZE = 35u;
                 std::vector<T> cmps;
};

}