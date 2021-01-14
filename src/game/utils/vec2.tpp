#include <game/utils/vec2.hpp>

namespace AIP {


template <typename NumType> constexpr vec2<NumType>::vec2(const NumType X,  const NumType Y ) noexcept : x(X), y(Y) { }

/* ASSIGMENT */
template <typename NumType> 
vec2<NumType>& 
vec2<NumType>::operator=(const vec2<NumType>& copy_from) noexcept { //copy assigment 
    x = copy_from.x; 
    y = copy_from.y; 
    return *this; 
}

template <typename NumType> 
vec2<NumType>& 
vec2<NumType>::operator=(vec2<NumType>&& move_from) noexcept { //move assigment
    x = std::exchange(move_from.x, 0); 
    y = std::exchange(move_from.y, 0);
    return *this;
}

template <typename NumType> 
vec2<NumType>& 
vec2<NumType>::operator+=(const vec2<NumType>& num) noexcept {
    x += num.x;
    y += num.y;
    return *this;
}

template <typename NumType> 
vec2<NumType>& 
vec2<NumType>::operator-=(const vec2<NumType>& num) noexcept {
    x -= num.x;
    y -= num.y;
    return *this;
}

template <typename NumType> 
vec2<NumType>& 
vec2<NumType>::operator*=(const vec2<NumType>& num) noexcept {
    x *= num.x;
    y *= num.y;
    return *this;
}

template <typename NumType> 
vec2<NumType>& 
vec2<NumType>::operator/=(const vec2<NumType>& num) noexcept {
    x /= num.x;
    y /= num.y;
    return *this;
}


/* OPERATIONS */
template <typename NumType> constexpr 
vec2<NumType>
vec2<NumType>::operator+(const vec2<NumType>& num) const noexcept {
    vec2<NumType> new_vec { };
    new_vec.x = x + num.x;
    new_vec.y = y + num.y;
    return new_vec;
}

template <typename NumType> constexpr
vec2<NumType>
vec2<NumType>::operator-(const vec2<NumType>& num) const noexcept {
    vec2<NumType> new_vec { };
    new_vec.x = x - num.x; 
    new_vec.y = y - num.y; 
    return new_vec;
}

template <typename NumType> constexpr 
vec2<NumType> 
vec2<NumType>::operator*(const vec2<NumType>& num) const noexcept {
    vec2<NumType> new_vec { };
    new_vec.x = x * num.x; 
    new_vec.y = y * num.y; 
    return new_vec;
}

template <typename NumType> constexpr
vec2<NumType> 
vec2<NumType>::operator/(const vec2<NumType>& num) const noexcept {
    vec2<NumType> new_vec { };
    new_vec.x = x / num.x; 
    new_vec.y = y / num.y; 
    return new_vec;
}


/* OPERATIONS W/ NO VEC*/
template <typename NumType> constexpr
vec2<NumType> 
vec2<NumType>::operator+(const NumType& num) const noexcept {
    vec2<NumType> new_vec { };
    new_vec.x = x + num; 
    new_vec.y = y + num; 
    return new_vec;
}

template <typename NumType> constexpr
vec2<NumType> 
vec2<NumType>::operator-(const NumType& num) const noexcept {
    vec2<NumType> new_vec { };
    new_vec.x = x - num; 
    new_vec.y = y - num; 
    return new_vec;
}

template <typename NumType> constexpr
vec2<NumType> 
vec2<NumType>::operator*(const NumType& num) const noexcept {
    vec2<NumType> new_vec { };
    new_vec.x = x * num; 
    new_vec.y = y * num; 
    return new_vec;
}

template <typename NumType> constexpr
vec2<NumType> 
vec2<NumType>::operator/(const NumType& num) const noexcept {
    vec2<NumType> new_vec { };
    new_vec.x = x / num; 
    new_vec.y = y / num; 
    return new_vec;
}


/* FUNCTIONS */
template <typename NumType>constexpr 
NumType 
vec2<NumType>::length() const noexcept {
    return std::sqrt( (x * x) + (y * y) );
}

template <typename NumType> constexpr
NumType
vec2<NumType>::length2() const noexcept {
    return (x*x) + (y*y);
}

template <typename NumType> constexpr 
void 
vec2<NumType>::normalize() noexcept {
    auto module = length();
    
    if(module != 0) {
        x /= module; y /= module;
    }
    else {
        x = 0; y = 0;
    }
}

}