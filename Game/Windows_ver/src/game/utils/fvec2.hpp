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
#include <game/utils/fint_t.tpp>

#include <cmath>
#include <utility>

namespace AIP {


template<typename NumType>
struct fvec2 {
    fvec2() = default;
    constexpr          fvec2(const NumType X,  const NumType Y ) noexcept : x(X), y(Y) { };
    constexpr          fvec2(const fvec2<NumType>& cpy_vec)      noexcept = default; //cpy ctor
    constexpr          fvec2(fvec2<NumType>&& mov_vec)           noexcept = default; //move ctor

    NumType x = 0l;
    NumType y = 0l;

/* ASSIGMENT */
    fvec2<NumType>& operator=(const fvec2<NumType>& copy_from) noexcept;
    fvec2<NumType>& operator=(fvec2<NumType>&& move_from)      noexcept;
    fvec2<NumType>& operator+=(const fvec2<NumType>& num)      noexcept;
    fvec2<NumType>& operator-=(const fvec2<NumType>& num)      noexcept;
    fvec2<NumType>& operator*=(const fvec2<NumType>& num)      noexcept;
    fvec2<NumType>& operator/=(const fvec2<NumType>& num)      noexcept;

/* ASSIGMENT W/ NO VEC*/
    fvec2<NumType>& operator=(const NumType& copy_from) noexcept;
    fvec2<NumType>& operator=(NumType&& move_from)      noexcept;
    fvec2<NumType>& operator+=(const NumType& num)      noexcept;
    fvec2<NumType>& operator-=(const NumType& num)      noexcept;
    fvec2<NumType>& operator*=(const NumType& num)      noexcept;
    fvec2<NumType>& operator/=(const NumType& num)      noexcept;

/* OPERATIONS */
    constexpr fvec2<NumType> operator+(const fvec2<NumType>& num) const noexcept;
    constexpr fvec2<NumType> operator-(const fvec2<NumType>& num) const noexcept;
    constexpr fvec2<NumType> operator*(const fvec2<NumType>& num) const noexcept;
    constexpr fvec2<NumType> operator/(const fvec2<NumType>& num) const noexcept;

/* OPERATIONS W/ NO VEC*/
    constexpr fvec2<NumType> operator+(const NumType& num) const noexcept;
    constexpr fvec2<NumType> operator-(const NumType& num) const noexcept;
    constexpr fvec2<NumType> operator*(const NumType& num) const noexcept;
    constexpr fvec2<NumType> operator/(const NumType& num) const noexcept;

/* FUNCTIONS */
    constexpr auto    length()     const noexcept;
    constexpr NumType length_fix() const noexcept;
    constexpr NumType length2()    const noexcept;
    constexpr void    normalize()        noexcept;
    constexpr void    setZero()          noexcept;
};





}// NS
