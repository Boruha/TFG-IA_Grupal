#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <game/utils/Color.hpp>
#include <game/utils/Vec2.hpp>

namespace AIP {

struct RenderComponent : BECS::Component_t {
    explicit RenderComponent(const BECS::entID entityID, const ufixed64_t s_W, const ufixed64_t s_H, const Color col) 
        : Component_t(entityID), sprite(s_W, s_H), sprite_C(col) { }

    ufixed_vec2 sprite { 0u, 0u };
    Color sprite_C { Color::Red };
};

}
