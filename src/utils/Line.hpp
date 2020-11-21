#pragma once

#include <utils/Vec2.hpp>
#include <utils/Color.hpp>

#include <cmath>

namespace AIP {

struct Line {
    constexpr Line() = default;
    constexpr explicit Line(const fixed_vec2& p0, const fixed_vec2& p1, Color col)
        : P0(p0), P1(p1), dX(p1.x - p0.x), dY(p1.y - p0.y), color(col) { }
    constexpr Line(const Line& l)
        : P0(l.P0), P1(l.P1), dX(l.dX), dY(l.dY), color(l.color) { } //copy ctor
    constexpr Line(Line&& l)
        : P0(std::move(l.P0)), P1(std::move(l.P1)), dX(std::move(l.dX)), dY(std::move(l.dY)), color(std::move(l.color)) { } //move ctor
    
    fixed_vec2 P0 { 0, 0 };
    fixed_vec2 P1 { 0, 0 };
    fixed64_t dX { 0l };
    fixed64_t dY { 0l };

    Color color { Color::White };
};

}