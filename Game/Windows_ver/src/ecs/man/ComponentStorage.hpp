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
#include <ecs/cmp/CmpVector_t.tpp>

#include <unordered_map>
#include <memory>
#include <optional>
#include <functional>

namespace BECS {

struct ComponentStorage {
    template <typename ref>
    using opt_refw = std::optional< std::reference_wrapper<ref> >;
    
      explicit ComponentStorage()                         = default;
             
               ComponentStorage(const ComponentStorage& ) = delete;
               ComponentStorage(const ComponentStorage&&) = delete;
    ComponentStorage& operator=(const ComponentStorage& ) = delete;
    ComponentStorage& operator=(const ComponentStorage&&) = delete;

    void clear() noexcept;


    template<typename T>               constexpr       T&              createComponent(const T& new_cmp) noexcept;

    template<typename T> [[nodiscard]] constexpr       std::vector<T>& getCmpCollection()                noexcept;

    template<typename T> [[nodiscard]] constexpr       T&              getCmpByEntityID(const entID eid) noexcept;

    bool deleteCmpByTypeIDAndEntityID(cmpTypeID cid, entID eid) noexcept;

private:
    std::unordered_map<std::size_t , std::unique_ptr<CmpCollection>> cmp_map;
};

}