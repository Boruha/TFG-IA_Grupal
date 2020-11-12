#pragma once

#include <cmath>
#include <iostream>
#include <utility>

#include <utils/ufixed32_t.hpp>

namespace AIP {

template<typename T>
struct vec2 {
    vec2<T>() = default;
    constexpr explicit vec2<T>(const T  X,  const T  Y ) : x(X), y(Y) { }
    constexpr vec2<T>(const vec2<T>& cpy_vec) : x(cpy_vec.x), y(cpy_vec.y) { } //cpy ctor
    constexpr vec2<T>(vec2<T>&& mov_vec)      : x(std::move(mov_vec.x)), y(std::move(mov_vec.y)) { } //move ctor

    T x { 0 };
    T y { 0 };

    /* OPERATORS */
    vec2<T>& operator=(const vec2<T>& copy_from) { //copy assigment 
        x = copy_from.x; 
        y = copy_from.y; 
        return *this; 
    }

    vec2<T>& operator=(vec2<T>&& move_from) noexcept { //move assigment
        x = std::move(move_from.x); 
        y = std::move(move_from.y);
        return *this;
    }

    vec2<T>& operator+=(const vec2<T>& num) {
        x += num.x;
        y += num.y;
        return *this;
    }

    vec2<T>& operator-=(const vec2<T>& num) {
        x -= num.x;
        y -= num.y;
        return *this;
    }

    vec2<T> operator+(const vec2<T>& num) const {
        vec2<T> new_vec { };
        new_vec.x = this->x + num.x;
        new_vec.y = this->y + num.y;
        return new_vec;
    }

    vec2<T> operator-(const vec2<T>& num) const {
        vec2<T> new_vec { };
        new_vec.x = this->x - num.x; 
        new_vec.y = this->y - num.y; 
        return new_vec;
    }

    vec2<T> operator*(const vec2<T>& num) const {
        vec2<T> new_vec { };
        new_vec.x = this->x * num.x; 
        new_vec.y = this->y * num.y; 
        return new_vec;
    }

    /* FUNCTIONS */
    constexpr T 
    length() {
        return std::sqrt( (x * x) + (y * y) );
    }

    constexpr T 
    length2() {
        return (x*x) + (y*y);
    }

    constexpr void 
    normalize() {
        auto module = length();
        if(module != 0) {
            x /= module;
            y /= module;
        }
        else
        {
            x = 0;
            y = 0;
        }
        
    }
};

struct fixed_vec2 {
    fixed_vec2() = default;
    constexpr explicit fixed_vec2(const fixed32_t  X,  const fixed32_t  Y ) : x(X), y(Y) { }
    constexpr explicit fixed_vec2(const int32_t    X,  const int32_t    Y ) : x(X), y(Y) { }
    constexpr fixed_vec2(const fixed_vec2& cpy_vec) : x(cpy_vec.x), y(cpy_vec.y) { } //cpy ctor
    constexpr fixed_vec2(fixed_vec2&& mov_vec)      : x(std::move(mov_vec.x)), y(std::move(mov_vec.y)) { } //move ctor

    fixed32_t x { 0 };
    fixed32_t y { 0 };

    /* OPERATORS */
    fixed_vec2& operator=(const fixed_vec2& copy_from) { //copy assigment 
        x = copy_from.x; 
        y = copy_from.y;
        return *this; 
    }

    fixed_vec2& operator=(fixed_vec2&& move_from) noexcept { //move assigment
        x = std::move(move_from.x); 
        y = std::move(move_from.y);
        return *this;
    }

    fixed_vec2& operator+=(const fixed_vec2& num) {
        x += num.x;
        y += num.y;
        return *this;
    }

    fixed_vec2& operator-=(const fixed_vec2& num) {
        x -= num.x;
        y -= num.y;
        return *this;
    }

    fixed_vec2 operator+(const fixed_vec2& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x + num.x;
        new_vec.y = this->y + num.y;
        return new_vec;
    }

    fixed_vec2 operator-(const fixed_vec2& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x - num.x; 
        new_vec.y = this->y - num.y; 
        return new_vec;
    }

    fixed_vec2 operator*(const fixed_vec2& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x * num.x; 
        new_vec.y = this->y * num.y; 
        return new_vec;
    }

    fixed_vec2 operator*(const int32_t& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x * num; 
        new_vec.y = this->y * num; 
        return new_vec;
    }

    fixed_vec2 operator*(const fixed32_t& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x * num; 
        new_vec.y = this->y * num; 
        return new_vec;
    }


    /* FUNCTIONS */
    constexpr int32_t
    length() {
        return std::sqrt( (x.getNoScaled() * x.getNoScaled()) + (y.getNoScaled() * y.getNoScaled() ) );
    }

    constexpr fixed32_t
    length2() {
        return (x*x) + (y*y);
    }

    constexpr void
    normalize() {
        auto module = length();
        if(module != 0) {
            x /= module;
            y /= module;
        }
        else
        {
            x.number = 0;
            y.number = 0;
        }
        
    }
};

struct ufixed_vec2 {
    ufixed_vec2() = default;
    constexpr explicit ufixed_vec2(const ufixed32_t  X,  const ufixed32_t  Y ) : x(X), y(Y) { }
    constexpr explicit ufixed_vec2(const uint32_t    X,  const uint32_t    Y ) : x(X), y(Y) { }
    constexpr ufixed_vec2(const ufixed_vec2& cpy_vec) : x(cpy_vec.x), y(cpy_vec.y) { } //cpy ctor
    constexpr ufixed_vec2(ufixed_vec2&& mov_vec)      : x(std::move(mov_vec.x)), y(std::move(mov_vec.y)) { } //move ctor
    
    ufixed32_t x { 0u };
    ufixed32_t y { 0u };

    /* OPERATORS */
    ufixed_vec2& operator=(const ufixed_vec2& copy_from) { //copy assigment 
        x = copy_from.x; 
        y = copy_from.y; 
        return *this; 
    }

    ufixed_vec2& operator=(ufixed_vec2&& move_from) noexcept { //move assigment
        x = std::move(move_from.x); 
        y = std::move(move_from.y);
        return *this;
    }

    ufixed_vec2& operator+=(const ufixed_vec2& num) {
        x += num.x;
        y += num.y;
        return *this;
    }

    ufixed_vec2& operator-=(const ufixed_vec2& num) {
        x -= num.x;
        y -= num.y;
        return *this;
    }

    ufixed_vec2 operator+(const ufixed_vec2& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x + num.x;
        new_vec.y = this->y + num.y;
        return new_vec;
    }

    ufixed_vec2 operator-(const ufixed_vec2& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x - num.x; 
        new_vec.y = this->y - num.y; 
        return new_vec;
    }

    ufixed_vec2 operator*(const ufixed_vec2& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x * num.x; 
        new_vec.y = this->y * num.y; 
        return new_vec;
    }

    ufixed_vec2 operator*(const uint32_t& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x * num; 
        new_vec.y = this->y * num; 
        return new_vec;
    }

    ufixed_vec2 operator*(const ufixed32_t& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x * num; 
        new_vec.y = this->y * num; 
        return new_vec;
    }

    /* FUNCTIONS */
    constexpr uint32_t
    length() {
        return std::sqrt( (x.getNoScaled() * x.getNoScaled()) + (y.getNoScaled() * y.getNoScaled() ) );
    }

    constexpr ufixed32_t
    length2() {
        return (x*x) + (y*y);
    }

    constexpr void
    normalize() {
        auto module = length();
        if(module != 0) {
            x /= module;
            y /= module;
        }
        else
        {
            x.number = 0;
            y.number = 0;
        }   
    }
};

}// NS
