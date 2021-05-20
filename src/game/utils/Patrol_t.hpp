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
#include <game/utils/fvec2.hpp>
#include <array>

namespace AIP {

struct Patrol_t {
    using Point2D_t = fvec2<fint_t<int64_t>>;

    static const std::size_t sz { 4u };
    std::array<Point2D_t, sz> points { };
    
    struct iterator {
        bool operator==(iterator const& oIt)
            { return index == oIt.index; }

        bool operator!=(iterator const& oIt)
            { return index != oIt.index; }

        void operator++() 
            { index = (index+1) % sz; }

        Point2D_t& operator*()
            { return (*point_ptr)[index]; }
        
        std::size_t index { 0u };
        std::array<Point2D_t, sz>* point_ptr { nullptr };
    };

    iterator begin() { return { 0 , &points }; }
    iterator end()   { return { sz, &points }; }
};

} //NS