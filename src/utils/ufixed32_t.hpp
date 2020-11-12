#pragma once
#include <cstdint>
#include <utility>

namespace AIP {

constexpr const uint32_t SCALE   { 256u };
constexpr const int32_t  SCALE_S { 256 };

struct fixed32_t {
    fixed32_t() = default;
    constexpr explicit fixed32_t(int32_t num) noexcept : number(num * SCALE_S)           { } //ctor
    constexpr explicit fixed32_t(float   num) noexcept : number(num * SCALE_S)           { } //ctor
    constexpr fixed32_t(const fixed32_t& num) noexcept : number(num.number)            { } //copy ctor
    constexpr fixed32_t(fixed32_t&& num)      noexcept : number(std::move(num.number)) { } //move ctor

    fixed32_t& operator=(const fixed32_t& copy_from) { //copy assigment 
        number = copy_from.number; 
        return *this; 
    }

    fixed32_t& operator=(fixed32_t&& move_from) noexcept { //move assigment
        number = std::move(move_from.number); 
        return *this;
    }

    fixed32_t& operator+=(const fixed32_t& num) {
        number += num.number;
        return *this;
    }

    fixed32_t& operator-=(const fixed32_t& num) {
        number -= num.number;
        return *this;
    }

    constexpr fixed32_t operator+(const fixed32_t& num) const {
        fixed32_t new_uf32_t { };
        new_uf32_t.number = this->number + num.number; 
        return new_uf32_t;
    }

    constexpr fixed32_t operator-(const fixed32_t& num) const {
        fixed32_t new_uf32_t { };
        new_uf32_t.number = this->number - num.number; 
        return new_uf32_t;
    }

    constexpr fixed32_t operator*(const fixed32_t& num) const {
        fixed32_t new_uf32_t { };
        new_uf32_t.number = ( (this->number/SCALE_S) * (num.number/SCALE_S) ) * SCALE_S; //desbordamiento (posibilidad de scale_S max8)
        return new_uf32_t;
    }

    constexpr fixed32_t operator*(const int32_t& num) const {
        fixed32_t new_uf32_t { };
        new_uf32_t.number = this->number * num;
        return new_uf32_t; 
    }

    constexpr fixed32_t operator/(const fixed32_t& num) const {
        fixed32_t new_uf32_t { };
        new_uf32_t.number = (this->number / num.number) * SCALE_S; 
        return new_uf32_t;
    }

    constexpr fixed32_t operator/(const int32_t& num) const {
        fixed32_t new_uf32_t { };
        new_uf32_t.number = this->number / num;
        return new_uf32_t;
    }

    fixed32_t& operator/=(const int32_t& num) {
        number /= num;
        return *this;
    }

    fixed32_t& operator/=(const fixed32_t& num) {
        number = (this->number / num.number) * SCALE_S;
        return *this;
    }

    constexpr bool operator>(const fixed32_t& num) const {
        return this->number > num.number;
    }

    constexpr bool operator<(const fixed32_t& num) const {
        return this->number < num.number;
    }

    constexpr bool operator!=(const fixed32_t& num) const {
        return this->number != num.number;
    }

    constexpr int32_t getNoScaled() const { return number/SCALE_S; }

    int32_t number { 0 };
};

struct ufixed32_t {
    ufixed32_t() = default;
    constexpr explicit ufixed32_t(uint32_t num) noexcept : number(num * SCALE)           { } //ctor
    constexpr explicit ufixed32_t(float    num) noexcept : number(num * SCALE)           { } //ctor
    constexpr ufixed32_t(const ufixed32_t& num) noexcept : number(num.number)            { } //copy ctor
    constexpr ufixed32_t(ufixed32_t&& num)      noexcept : number(std::move(num.number)) { } //move ctor

    explicit operator fixed32_t() const { return fixed32_t( static_cast<int32_t>((number/SCALE)) ); };

    ufixed32_t& operator=(const ufixed32_t& copy_from) { //copy assigment 
        number = copy_from.number; 
        return *this; 
    }

    ufixed32_t& operator=(ufixed32_t&& move_from) noexcept { //move assigment
        number = std::move(move_from.number); 
        return *this;
    }

    ufixed32_t& operator+=(const ufixed32_t& num) {
        number += num.number;
        return *this;
    }

    ufixed32_t& operator-=(const ufixed32_t& num) {
        number -= num.number;
        return *this;
    }

    constexpr ufixed32_t operator+(const ufixed32_t& num) const {
        ufixed32_t new_uf32_t { };
        new_uf32_t.number = this->number + num.number; 
        return new_uf32_t;
    }

    constexpr ufixed32_t operator-(const ufixed32_t& num) const {
        ufixed32_t new_uf32_t { };
        new_uf32_t.number = this->number - num.number; 
        return new_uf32_t;
    }
    /* op* con ufixed32_t */
    constexpr ufixed32_t operator*(const ufixed32_t& num) const {
        ufixed32_t new_uf32_t { };
        new_uf32_t.number = ( (this->number/SCALE) * (num.number/SCALE) ) * SCALE; //desbordamiento (posibilidad de scale max8)
        return new_uf32_t;
    }
    /* op* con uint32_t */
    constexpr ufixed32_t operator*(const uint32_t& num) const {
        ufixed32_t new_uf32_t { };
        new_uf32_t.number = this->number * num;
        return new_uf32_t; 
    }

    constexpr ufixed32_t operator/(const ufixed32_t& num) const {
        ufixed32_t new_uf32_t { };
        new_uf32_t.number = (this->number / num.number) * SCALE; 
        return new_uf32_t;
    }

    constexpr ufixed32_t operator/(const uint32_t& num) const {
        ufixed32_t new_uf32_t { };
        new_uf32_t.number = this->number / num;
        return new_uf32_t;
    }

    ufixed32_t& operator/=(const uint32_t& num) {
        number /= num;
        return *this;
    }

    ufixed32_t& operator/=(const ufixed32_t& num) {
        number = (this->number / num.number) * SCALE;
        return *this;
    }

    constexpr bool operator>(const ufixed32_t& num) const {
        return this->number > num.number;
    }

    constexpr bool operator<(const ufixed32_t& num) const {
        return this->number < num.number;
    }

    constexpr bool operator!=(const ufixed32_t& num) const {
        return this->number != num.number;
    }

    constexpr uint32_t getNoScaled() const { return number/SCALE; }

    uint32_t number { 0u };
};

}