#pragma once
#include <cmp/Component_t.hpp>

#include <utils/Color.hpp>
#include <utils/Vec2.hpp>

namespace AIP {

struct RenderComponent : Component_t {
    explicit RenderComponent(const entID entityID, const ufixed64_t s_W, const ufixed64_t s_H, const Color col) 
        : Component_t(entityID), sprite(s_W, s_H), sprite_C(col) { }

    ufixed_vec2 sprite { 0u, 0u };
    Color sprite_C { Color::Red };
};

}
