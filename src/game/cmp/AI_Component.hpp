#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <game/utils/Vec2.hpp>

#include <vector>

namespace AIP {

enum class AI_behaviour : uint16_t {
    no_b     = 0u,
    patrol_b = 1u,
    chase_b  = 2u,
    runaway_b= 3u,
    pursue_b = 4u,
    evade_b  = 5u,
    attack_b = 6u
};

//hay que pasar el objetivo a un parametro y crear setters.
struct AI_Component : BECS::Component_t {
    explicit AI_Component(BECS::entID eid) : Component_t(eid) { }

    std::vector<fixed_vec2> target_vec { fixed_vec2 { -300, -300 }, fixed_vec2 {  200, -300 }
                                       , fixed_vec2 {  200,  200 }, fixed_vec2 { -300,  200 } };
    std::size_t target_index { 0u };
    AI_behaviour current_behavior { AI_behaviour::patrol_b };
};

} //NS