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

#include <ecs/cmp/CmpVector_t.hpp>

#include <algorithm>

namespace BECS {

template <typename T>
CmpVector<T>::CmpVector() {
    cmps.reserve(MAX_CMP_SIZE);
}

template <typename T>
bool 
CmpVector<T>::deleteCmpByEntityID(entID eid) noexcept {
    auto result = true;
    auto it_cmp = findCmpByEntityID(eid);
    
    if(!it_cmp) 
        result = false;
    else {
        auto it = *it_cmp;

        if( it + 1 != cmps.end() )
            *it = cmps.back();

        cmps.pop_back();
    }

    return result;
}

template <typename T>
auto
CmpVector<T>::findCmpByEntityID(entID eid) noexcept {
    std::optional it_cmp = std::find_if(cmps.begin(), cmps.end(), 
            [&eid](T& cmp) { 
                return cmp.getEntityID() == eid; 
            }
        );
        
    if( it_cmp == cmps.end() )
        it_cmp.reset();

    return it_cmp;
}

}