#pragma once

#include <cstdint>
#include <utility>

//en el futuro intentar templarizar ya que son iguales
namespace AIP {

constexpr const uint64_t SCALE   { 65536u };
constexpr const int64_t  SCALE_S { 65536 };

struct fixed64_t {
    fixed64_t() = default;
    constexpr explicit fixed64_t(int64_t num) noexcept : number(num * SCALE_S)           { } //ctor
    constexpr explicit fixed64_t(float   num) noexcept : number(num * SCALE_S)           { } //ctor
    constexpr fixed64_t(const fixed64_t& num) noexcept : number(num.number)            { } //copy ctor
    constexpr fixed64_t(fixed64_t&& num)      noexcept : number(std::move(num.number)) { } //move ctor

    fixed64_t& operator=(const fixed64_t& copy_from) { //copy assigment 
        number = copy_from.number; 
        return *this; 
    }

    fixed64_t& operator=(fixed64_t&& move_from) noexcept { //move assigment
        number = std::move(move_from.number); 
        return *this;
    }

    fixed64_t& operator+=(const fixed64_t& num) {
        number += num.number;
        return *this;
    }

    fixed64_t& operator-=(const fixed64_t& num) {
        number -= num.number;
        return *this;
    }

    constexpr fixed64_t operator+(const fixed64_t& num) const {
        fixed64_t new_uf64_t { };
        new_uf64_t.number = this->number + num.number; 
        return new_uf64_t;
    }

    constexpr fixed64_t operator+(const int64_t& num) const {
        fixed64_t new_uf64_t { };
        new_uf64_t.number = this->number + (num * SCALE_S); 
        return new_uf64_t;
    }

    constexpr fixed64_t operator+=(const int64_t& num) {
        number += (num * SCALE_S); 
        return *this;
    }

    constexpr fixed64_t operator-(const fixed64_t& num) const {
        fixed64_t new_uf64_t { };
        new_uf64_t.number = this->number - num.number; 
        return new_uf64_t;
    }

    constexpr fixed64_t operator-(const int64_t& num) const {
        fixed64_t new_uf64_t { };
        new_uf64_t.number = this->number - (num * SCALE_S);
        return new_uf64_t;
    }

    constexpr fixed64_t operator*(const fixed64_t& num) const {
        fixed64_t new_uf64_t { };
        new_uf64_t.number = ( this->number * num.number ) / SCALE_S;
        return new_uf64_t;
    }

    constexpr fixed64_t operator*(const int64_t& num) const {
        fixed64_t new_uf64_t { };
        new_uf64_t.number = this->number * num;
        return new_uf64_t; 
    }

    constexpr fixed64_t operator*=(const fixed64_t& num) {
        this->number = (this->number * num.number) / SCALE_S;
        return *this;
    }

    constexpr fixed64_t operator/(const fixed64_t& num) const {
        fixed64_t new_uf64_t { };
        new_uf64_t.number = (this->number / num.number) * SCALE_S; 
        return new_uf64_t;
    }

    constexpr fixed64_t operator/(const int64_t& num) const {
        fixed64_t new_uf64_t { };
        new_uf64_t.number = this->number / num;
        return new_uf64_t;
    }

    fixed64_t& operator/=(const int64_t& num) {
        number /= num;
        return *this;
    }

    fixed64_t& operator/=(const fixed64_t& num) {
        number = (this->number / num.number) * SCALE_S;
        return *this;
    }

    constexpr bool operator>(const fixed64_t& num) const {
        return this->number > num.number;
    }

    constexpr bool operator<(const fixed64_t& num) const {
        return this->number < num.number;
    }

    constexpr bool operator!=(const fixed64_t& num) const {
        return this->number != num.number;
    }

    constexpr int64_t getNoScaled() const { return number/SCALE_S; }

    int64_t number { 0 };
};

struct ufixed64_t {
    ufixed64_t() = default;
    constexpr explicit ufixed64_t(uint64_t num) noexcept : number(num * SCALE)           { } //ctor
    constexpr explicit ufixed64_t(float    num) noexcept : number(num * SCALE)           { } //ctor
    constexpr ufixed64_t(const ufixed64_t& num) noexcept : number(num.number)            { } //copy ctor
    constexpr ufixed64_t(ufixed64_t&& num)      noexcept : number(std::move(num.number)) { } //move ctor

    explicit operator fixed64_t() const { return fixed64_t( static_cast<int64_t>((number/SCALE)) ); };

    ufixed64_t& operator=(const ufixed64_t& copy_from) { //copy assigment 
        number = copy_from.number; 
        return *this; 
    }

    ufixed64_t& operator=(ufixed64_t&& move_from) noexcept { //move assigment
        number = std::move(move_from.number); 
        return *this;
    }

    ufixed64_t& operator+=(const ufixed64_t& num) {
        number += num.number;
        return *this;
    }

    ufixed64_t& operator-=(const ufixed64_t& num) {
        number -= num.number;
        return *this;
    }

    constexpr ufixed64_t operator+(const ufixed64_t& num) const {
        ufixed64_t new_uf64_t { };
        new_uf64_t.number = this->number + num.number; 
        return new_uf64_t;
    }

    constexpr ufixed64_t operator+(const uint64_t& num) const {
        ufixed64_t new_uf64_t { };
        new_uf64_t.number = this->number + (num * SCALE);
        return new_uf64_t;
    }

    constexpr ufixed64_t operator-(const ufixed64_t& num) const {
        ufixed64_t new_uf64_t { };
        new_uf64_t.number = this->number - num.number; 
        return new_uf64_t;
    }

    constexpr ufixed64_t operator-(const uint64_t& num) const {
        ufixed64_t new_uf64_t { };
        new_uf64_t.number = this->number - (num * SCALE);
        return new_uf64_t;
    }

    constexpr ufixed64_t operator*(const ufixed64_t& num) const {
        ufixed64_t new_uf64_t { };
        new_uf64_t.number = ( this->number * num.number ) / SCALE;
        return new_uf64_t;
    }

    constexpr ufixed64_t operator*(const uint64_t& num) const {
        ufixed64_t new_uf64_t { };
        new_uf64_t.number = this->number * num;
        return new_uf64_t; 
    }

    constexpr ufixed64_t operator*=(const ufixed64_t& num) {
        this->number = (this->number * num.number) / SCALE;
        return *this;
    }

    constexpr ufixed64_t operator/(const ufixed64_t& num) const {
        ufixed64_t new_uf64_t { };
        new_uf64_t.number = (this->number / num.number) * SCALE; 
        return new_uf64_t;
    }

    constexpr ufixed64_t operator/(const uint64_t& num) const {
        ufixed64_t new_uf64_t { };
        new_uf64_t.number = this->number / num;
        return new_uf64_t;
    }

    ufixed64_t& operator/=(const uint64_t& num) {
        number /= num;
        return *this;
    }

    ufixed64_t& operator/=(const ufixed64_t& num) {
        number = (this->number / num.number) * SCALE;
        return *this;
    }

    constexpr bool operator>(const ufixed64_t& num) const {
        return this->number > num.number;
    }

    constexpr bool operator<(const ufixed64_t& num) const {
        return this->number < num.number;
    }

    constexpr bool operator!=(const ufixed64_t& num) const {
        return this->number != num.number;
    }

    constexpr uint64_t getNoScaled() const { return number/SCALE; }

    uint64_t number { 0u };
};

} // NS