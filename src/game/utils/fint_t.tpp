#include <game/utils/fint_t.hpp>

namespace AIP {

/* CTORS & COPY/MOVE */
template <typename NumType> constexpr fint_t<NumType>::fint_t(NumType num)                noexcept : number(num * SCALE)           { } //ctor
template <typename NumType> constexpr fint_t<NumType>::fint_t(float   num)                noexcept : number(num * SCALE)           { } //ctor
template <typename NumType> constexpr fint_t<NumType>::fint_t(const fint_t<NumType>& num) noexcept : number(num.number)            { } //copy ctor
template <typename NumType> constexpr fint_t<NumType>::fint_t(fint_t<NumType>&& num)      noexcept : number(std::move(num.number)) { } //move ctor


/* ASSIGMENT */
template <typename NumType>
fint_t<NumType>& 
fint_t<NumType>::operator=(const fint_t<NumType>& copy_from) noexcept{ //copy assigment 
    number = copy_from.number; 
    return *this; 
}

template <typename NumType>
fint_t<NumType>& 
fint_t<NumType>::operator=(fint_t<NumType>&& move_from) noexcept { //move assigment
    number = std::move(move_from.number);
    return *this;
}

template <typename NumType> constexpr
fint_t<NumType>& 
fint_t<NumType>::operator+=(const fint_t<NumType>& num) noexcept {
    number += num.number;
    return *this;
}

template <typename NumType> constexpr
fint_t<NumType>& 
fint_t<NumType>::operator-=(const fint_t<NumType>& num) noexcept {
    number -= num.number;
    return *this;
}

template <typename NumType> constexpr 
fint_t<NumType>& 
fint_t<NumType>::operator*=(const fint_t<NumType>& num) noexcept {
    this->number = (this->number * num.number) / SCALE_S;
    return *this;
}

template <typename NumType> constexpr 
fint_t<NumType>&
fint_t<NumType>::operator/=(const fint_t<NumType>& num) noexcept {
    number = (number / num.number) * SCALE;
    return *this;
}

/* ASSIGMENT W/ BASE TYPE */
template <typename NumType> constexpr
fint_t<NumType>& 
fint_t<NumType>::operator+=(const NumType& num) noexcept {
    number += (num * SCALE);
    return *this;
}

template <typename NumType> constexpr
fint_t<NumType>& 
fint_t<NumType>::operator-=(const NumType& num) noexcept {
    number -= (num * SCALE);
    return *this;
}

template <typename NumType> constexpr 
fint_t<NumType>& 
fint_t<NumType>::operator*=(const NumType& num) noexcept {
    number *= num;
    return *this;
}

template <typename NumType> constexpr 
fint_t<NumType>& 
fint_t<NumType>::operator/=(const NumType& num) noexcept {
    number /= num;
    return *this;
}


/* OPERATIONS */
template <typename NumType> constexpr
fint_t<NumType> 
fint_t<NumType>::operator+(const fint_t<NumType>& num) const noexcept {
    fint_t<NumType> new_t { };
    new_t.number = number + num.number; 
    return new_t;
}

template <typename NumType> constexpr
fint_t<NumType>
fint_t<NumType>::operator-(const fint_t<NumType>& num) const noexcept {
    fint_t<NumType> new_t { };
    new_t.number = number - num.number; 
    return new_t;
}

template <typename NumType> constexpr
fint_t<NumType> 
fint_t<NumType>::operator*(const fint_t<NumType>& num) const noexcept {
    fint_t<NumType> new_t { };
    new_t.number = ( number * num.number ) / SCALE;
    return new_t;
}

template <typename NumType> constexpr 
fint_t<NumType> 
fint_t<NumType>::operator/(const fint_t<NumType>& num) const noexcept {
    fint_t<NumType> new_t { };
    new_t.number = (number / num.number) * SCALE; 
    return new_t;
}


/* OPERATIONS W/ BASE TYPE */
template <typename NumType> constexpr
fint_t<NumType> 
fint_t<NumType>::operator+(const NumType& num) const noexcept {
    fint_t<NumType> new_t { };
    new_t.number = number + (num * SCALE); 
    return new_t;
}

template <typename NumType> constexpr 
fint_t<NumType> 
fint_t<NumType>::operator-(const NumType& num) const noexcept {
    fint_t<NumType> new_t { };
    new_t.number = number - (num * SCALE);
    return new_t;
}

template <typename NumType> constexpr
fint_t<NumType> 
fint_t<NumType>::operator*(const NumType& num) const noexcept {
    fint_t<NumType> new_t { };
    new_t.number = number * num;
    return new_t; 
}

template <typename NumType> constexpr 
fint_t<NumType> 
fint_t<NumType>::operator/(const NumType& num) const noexcept {
    fint_t<NumType> new_t { };
    new_t.number = number / num;
    return new_t;
}


/* LOGICAL COMPARATIONS */
template <typename NumType> constexpr 
bool 
fint_t<NumType>::operator>( const fint_t<NumType>& num) const noexcept {
    return number > num.number;
}

template <typename NumType> constexpr 
bool 
fint_t<NumType>::operator<( const fint_t<NumType>& num) const noexcept {
    return number < num.number;
}

template <typename NumType> constexpr 
bool 
fint_t<NumType>::operator!=(const fint_t<NumType>& num) const noexcept {
    return number != num.number;
}


/* GETTER */
template <typename NumType> constexpr 
NumType 
fint_t<NumType>::getNoScaled() const { 
    return number/SCALE; 
}




}