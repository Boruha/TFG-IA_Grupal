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

#include <ecs/man/ComponentStorage.hpp>

#include <cstdlib>

namespace BECS {

template<typename T> constexpr 
T& 
ComponentStorage::createComponent(const T& new_cmp) noexcept {
    auto&  cmp_vec_ref = getCmpCollection<T>();
    return cmp_vec_ref.emplace_back( new_cmp );
}

inline void 
ComponentStorage::clear() noexcept {
    cmp_map.clear();
}


template<typename T> constexpr 
std::vector<T>&
ComponentStorage::getCmpCollection() noexcept {
    opt_refw<std::vector<T>> result { };
    auto it = cmp_map.find(Component_t::getCmpTypeID<T>());

    if(it != end(cmp_map))
        result = static_cast<CmpVector<T>*>( it->second.get() )->cmps;

    else {
        auto& new_vec = cmp_map[Component_t::getCmpTypeID<T>()] = std::make_unique<CmpVector<T>>();
        result        = static_cast<CmpVector<T>*>( new_vec.get() )->cmps;
    }

    return (*result).get();
}

template<typename T> constexpr
T& 
ComponentStorage::getCmpByEntityID(const entID eid) noexcept {
    auto& cmp_vec_ref = getCmpCollection<T>();

    auto it_cmp = std::find_if(cmp_vec_ref.begin(), cmp_vec_ref.end(),
            [&eid](T& cmp) {
                return cmp.getEntityID() == eid;
            }
        );

    if( it_cmp == cmp_vec_ref.end() )
        std::exit(EXIT_FAILURE);

    return *it_cmp; //vec_iterator *-> cmp
}

inline bool 
ComponentStorage::deleteCmpByTypeIDAndEntityID(cmpTypeID cid, entID eid) noexcept {
    auto result = true;
    auto it     = cmp_map.find(cid);

    if(it == cmp_map.end())
        result = false;
    else
        result = it->second->deleteCmpByEntityID(eid);

    return result;
}

}
