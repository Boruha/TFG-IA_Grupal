#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <game/utils/Color.hpp>
#include <game/utils/vec2.hpp>

namespace AIP {

struct RenderComponent : BECS::Component_t {
    explicit RenderComponent(const BECS::entID entityID, const uint32_t s_W, const uint32_t s_H, const Color col) 
        : Component_t(entityID), sprite(s_W, s_H), sprite_C(col) { }

    vec2<uint32_t> sprite { 0u, 0u };
    Color sprite_C { Color::Red };
};

}
