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
#include <cmath>
#include <utility>


namespace AIP {

template<typename NumType>
struct vec2 {
    vec2() = default;
    constexpr explicit vec2(const NumType X,  const NumType Y ) noexcept;
    constexpr          vec2(const vec2<NumType>& cpy_vec)       noexcept = default; //cpy ctor
    constexpr          vec2(vec2<NumType>&& mov_vec)            noexcept = default; //move ctor

    NumType x { 0 };
    NumType y { 0 };

/* ASSIGMENT */
    vec2<NumType>& operator=(const vec2<NumType>& copy_from) noexcept;
    vec2<NumType>& operator=(vec2<NumType>&& move_from)      noexcept;
    vec2<NumType>& operator+=(const vec2<NumType>& num)      noexcept;
    vec2<NumType>& operator-=(const vec2<NumType>& num)      noexcept;
    vec2<NumType>& operator*=(const vec2<NumType>& num)      noexcept;
    vec2<NumType>& operator/=(const vec2<NumType>& num)      noexcept;

/* OPERATIONS */
    constexpr vec2<NumType> operator+(const vec2<NumType>& num) const noexcept;
    constexpr vec2<NumType> operator-(const vec2<NumType>& num) const noexcept;
    constexpr vec2<NumType> operator*(const vec2<NumType>& num) const noexcept;
    constexpr vec2<NumType> operator/(const vec2<NumType>& num) const noexcept;

/* OPERATIONS W/ NO VEC*/
    constexpr vec2<NumType> operator+(const NumType& num) const noexcept;
    constexpr vec2<NumType> operator-(const NumType& num) const noexcept;
    constexpr vec2<NumType> operator*(const NumType& num) const noexcept;
    constexpr vec2<NumType> operator/(const NumType& num) const noexcept;

/* FUNCTIONS */
    constexpr NumType length()    const noexcept;
    constexpr NumType length2()   const noexcept;
    constexpr void    normalize()       noexcept;
};

}