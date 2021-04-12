#pragma once
#include <cstdint>
#include <utility>

namespace AIP {

template <typename NumType>
struct fint_t {
    fint_t() = default;

    constexpr fint_t(NumType num)                noexcept; //ctor
    constexpr explicit fint_t(float   num)       noexcept; //ctor
    constexpr fint_t(const fint_t<NumType>& num) noexcept = default; //copy ctor
    constexpr fint_t(fint_t<NumType>&& num)      noexcept = default; //move ctor

/* ASSIGMENT */
              fint_t<NumType>& operator=(const fint_t<NumType>& copy_from) noexcept; //copy assigment
              fint_t<NumType>& operator=(fint_t<NumType>&& move_from)      noexcept; //move assigment
    constexpr fint_t<NumType>& operator+=(const fint_t<NumType>& num)      noexcept;
    constexpr fint_t<NumType>& operator-=(const fint_t<NumType>& num)      noexcept;
    constexpr fint_t<NumType>& operator*=(const fint_t<NumType>& num)      noexcept;
    constexpr fint_t<NumType>& operator/=(const fint_t<NumType>& num)      noexcept;

/* ASSIGMENT W/ BASE TYPE */
    constexpr fint_t<NumType>& operator+=(const NumType& num) noexcept;
    constexpr fint_t<NumType>& operator-=(const NumType& num) noexcept;
    constexpr fint_t<NumType>& operator*=(const NumType& num) noexcept;
    constexpr fint_t<NumType>& operator/=(const NumType& num) noexcept;

/* OPERATIONS */
    constexpr fint_t<NumType> operator+(const fint_t<NumType>& num) const noexcept;
    constexpr fint_t<NumType> operator-(const fint_t<NumType>& num) const noexcept;
    constexpr fint_t<NumType> operator*(const fint_t<NumType>& num) const noexcept;
    constexpr fint_t<NumType> operator/(const fint_t<NumType>& num) const noexcept;

/* OPERATIONS W/ BASE TYPE */
    constexpr fint_t<NumType> operator+(const NumType& num) const noexcept;
    constexpr fint_t<NumType> operator-(const NumType& num) const noexcept;
    constexpr fint_t<NumType> operator*(const NumType& num) const noexcept;
    constexpr fint_t<NumType> operator/(const NumType& num) const noexcept;

/* LOGICAL COMPARATIONS */
    constexpr bool operator>( const fint_t<NumType>& num) const noexcept;
    constexpr bool operator<( const fint_t<NumType>& num) const noexcept;
    constexpr bool operator!=(const fint_t<NumType>& num) const noexcept;

/* GETTERS */
    constexpr NumType getNoScaled() const noexcept;
    
/* DATA */    
                            NumType number { 0 };
    constexpr static inline NumType SCALE  { 65536 };
};


}