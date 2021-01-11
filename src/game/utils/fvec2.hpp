#pragma once
//#include <game/utils/ufixed64_t.hpp>
#include <game/utils/fint_t.tpp>

#include <cmath>
#include <iostream>
#include <utility>


namespace AIP {
/*
struct fixed_vec2 {
    fixed_vec2() = default;
    constexpr explicit fixed_vec2(const fixed64_t  X,  const fixed64_t  Y ) : x(X), y(Y) { }
    constexpr explicit fixed_vec2(const int64_t    X,  const int64_t    Y ) : x(X), y(Y) { }
    constexpr fixed_vec2(const fixed_vec2& cpy_vec) : x(cpy_vec.x), y(cpy_vec.y) { } //cpy ctor
    constexpr fixed_vec2(fixed_vec2&& mov_vec)      : x(std::move(mov_vec.x)), y(std::move(mov_vec.y)) { } //move ctor

    fixed64_t x { 0l };
    fixed64_t y { 0l };

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

    fixed_vec2 operator+(const int64_t& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x + num; 
        new_vec.y = this->y + num; 
        return new_vec;
    }

    fixed_vec2 operator+(const fixed64_t& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x + num; 
        new_vec.y = this->y + num; 
        return new_vec;
    }

    fixed_vec2 operator-(const fixed_vec2& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x - num.x; 
        new_vec.y = this->y - num.y; 
        return new_vec;
    }

    fixed_vec2 operator-(const int64_t& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x - num; 
        new_vec.y = this->y - num; 
        return new_vec;
    }

    fixed_vec2 operator-(const fixed64_t& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x - num; 
        new_vec.y = this->y - num;
        return new_vec;
    }

    fixed_vec2 operator*(const fixed_vec2& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x * num.x; 
        new_vec.y = this->y * num.y; 
        return new_vec;
    }

    fixed_vec2 operator*(const int64_t& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x * num; 
        new_vec.y = this->y * num; 
        return new_vec;
    }

    fixed_vec2 operator*(const fixed64_t& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x * num; 
        new_vec.y = this->y * num; 
        return new_vec;
    }

    fixed_vec2 operator*=(const fixed_vec2& num) {
        this->x *= num.x;
        this->y *= num.y;
        return *this;
    }

    fixed_vec2 operator*=(const fixed64_t& num) {
        this->x *= num;
        this->y *= num;
        return *this;
    }

    fixed_vec2 operator/(const int64_t& num) const {
        fixed_vec2 new_vec { };
        new_vec.x = this->x / num; 
        new_vec.y = this->y / num; 
        return new_vec;
    }

    fixed_vec2 operator/=(const fixed_vec2& num) {
        this->x /= num.x;
        this->y /= num.y;
        return *this;
    }

    fixed_vec2 operator/=(const fixed64_t& num) {
        this->x /= num;
        this->y /= num;
        return *this;
    }


    constexpr int64_t
    length() {
        return std::sqrt(( x.getNoScaled() * x.getNoScaled() ) + ( y.getNoScaled() * y.getNoScaled() ));
    }

    constexpr fixed64_t
    length_fix() {
        int64_t sqrt = std::sqrt(( x.getNoScaled() * x.getNoScaled() ) + ( y.getNoScaled() * y.getNoScaled() ));
        return fixed64_t( sqrt );
    }

    constexpr fixed64_t
    length2() {
        return (x*x) + (y*y);
    }

    constexpr const fixed64_t
    length2() const {
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
    constexpr explicit ufixed_vec2(const ufixed64_t  X,  const ufixed64_t  Y ) : x(X), y(Y) { }
    constexpr explicit ufixed_vec2(const uint64_t    X,  const uint64_t    Y ) : x(X), y(Y) { }
    constexpr ufixed_vec2(const ufixed_vec2& cpy_vec) : x(cpy_vec.x), y(cpy_vec.y) { } //cpy ctor
    constexpr ufixed_vec2(ufixed_vec2&& mov_vec)      : x(std::move(mov_vec.x)), y(std::move(mov_vec.y)) { } //move ctor
    
    ufixed64_t x { 0ul };
    ufixed64_t y { 0ul };

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

    ufixed_vec2 operator+(const uint64_t& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x + num; 
        new_vec.y = this->y + num;
        return new_vec;
    }

    ufixed_vec2 operator+(const ufixed64_t& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x + num; 
        new_vec.y = this->y + num;
        return new_vec;
    }

    ufixed_vec2 operator-(const ufixed_vec2& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x - num.x; 
        new_vec.y = this->y - num.y; 
        return new_vec;
    }

    ufixed_vec2 operator-(const uint64_t& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x - num; 
        new_vec.y = this->y - num;
        return new_vec;
    }

    ufixed_vec2 operator-(const ufixed64_t& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x - num; 
        new_vec.y = this->y - num;
        return new_vec;
    }

    ufixed_vec2 operator*(const ufixed_vec2& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x * num.x; 
        new_vec.y = this->y * num.y; 
        return new_vec;
    }

    ufixed_vec2 operator*(const uint64_t& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x * num; 
        new_vec.y = this->y * num; 
        return new_vec;
    }

    ufixed_vec2 operator*(const ufixed64_t& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x * num; 
        new_vec.y = this->y * num; 
        return new_vec;
    }

    ufixed_vec2 operator*=(const ufixed_vec2& num) {
        this->x *= num.x;
        this->y *= num.y;
        return *this;
    }

    ufixed_vec2 operator*=(const ufixed64_t& num) {
        this->x *= num;
        this->y *= num;
        return *this;
    }

    ufixed_vec2 operator/(const uint64_t& num) const {
        ufixed_vec2 new_vec { };
        new_vec.x = this->x / num; 
        new_vec.y = this->y / num; 
        return new_vec;
    }

    constexpr uint64_t
    length() {
        return std::sqrt( (x.getNoScaled() * x.getNoScaled()) + (y.getNoScaled() * y.getNoScaled() ) );
    }

    constexpr ufixed64_t
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

*/

template<typename NumType>
struct fvec2 {
    fvec2() = default;
    constexpr explicit fvec2(const NumType X,  const NumType Y ) noexcept;
    constexpr          fvec2(const fvec2<NumType>& cpy_vec)      noexcept; //cpy ctor
    constexpr          fvec2(fvec2<NumType>&& mov_vec)           noexcept; //move ctor

    NumType x { 0l };
    NumType y { 0l };

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
};





}// NS
