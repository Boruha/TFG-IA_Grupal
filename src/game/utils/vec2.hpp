#pragma once
#include <cmath>
#include <utility>


namespace AIP {

template<typename NumType>
struct vec2 {
    vec2() = default;
    constexpr explicit vec2(const NumType X,  const NumType Y ) noexcept;
    constexpr          vec2(const vec2<NumType>& cpy_vec)       noexcept; //cpy ctor
    constexpr          vec2(vec2<NumType>&& mov_vec)            noexcept; //move ctor

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