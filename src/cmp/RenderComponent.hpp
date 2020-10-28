#pragma once
#include <cmp/Component_t.hpp>

#include <utils/Color.hpp>
#include <utils/Vec2.hpp>

namespace AIP {

struct RenderComponent : Component_t {
    explicit RenderComponent(const entID entityID, const ufixed32_t s_W, const ufixed32_t s_H, const Color col) 
        : Component_t(entityID), sprite(s_W, s_H), head(s_W/4u, s_H/4u), sprite_C(col) { }

    const ufixed_vec2 sprite   { 0u, 0u };
    const ufixed_vec2 head     { 0u, 0u };
    const Color       sprite_C { Color::Red };
};

}
