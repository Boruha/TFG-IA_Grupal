#pragma once
#include <cmath>
#include <iostream>

#include <utils/AI_Constants.hpp>
#include <utils/ufixed32_t.hpp>

namespace AIP {

template<typename T>
struct Vec2 {
    Vec2<T>() = default;
    Vec2<T>(const T  X,  const T  Y ) : x(X), y(Y) { }

    T x { };
    T y { };

    T length() {
        return std::sqrt( ((x/SCALE) * (x/SCALE)) + ((y/SCALE) * (y/SCALE)) );
    }

    T length2() {
        return (((x/SCALE) * (x/SCALE)) * SCALE) + (((y/SCALE) * (y/SCALE)) * SCALE);
    }

    void normalize() {
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
    fixed_vec2(const fixed32_t  X,  const fixed32_t  Y ) : x(X), y(Y) { }
    fixed_vec2(const int32_t    X,  const int32_t    Y ) : x(X), y(Y) { }

    fixed32_t x { 0 };
    fixed32_t y { 0 };

    int32_t length() {
        return std::sqrt( (x.getNoScaled() * x.getNoScaled()) + (y.getNoScaled() * y.getNoScaled() ) );
    }

    fixed32_t length2() {
        return (x*x) + (y*y);
    }

    void normalize() {
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

struct ufixed_vec2 {
    ufixed_vec2() = default;
    ufixed_vec2(const ufixed32_t  X,  const ufixed32_t  Y ) : x(X), y(Y) { }
    ufixed_vec2(const uint32_t    X,  const uint32_t    Y ) : x(X), y(Y) { }

    ufixed32_t x { 0u };
    ufixed32_t y { 0u };

    uint32_t length() {
        return std::sqrt( (x.getNoScaled() * x.getNoScaled()) + (y.getNoScaled() * y.getNoScaled() ) );
    }

    ufixed32_t length2() {
        return (x*x) + (y*y);
    }

    void normalize() {
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

}// NS
