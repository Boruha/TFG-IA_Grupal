#pragma once
#include <cmp/Component_t.hpp>
#include <vector>

#include <utils/Vec2.hpp>

namespace AIP {

//enum class AI_behaviour : uint16_t {
//    no_b     = 0u,
//    patrol_b = 1u,
//    arrive_b  = 2u,
//    flee_b   = 3u,
//    pursue_b = 4u,
//    evade_b  = 5u
//};

struct AI_Component : Component_t {
    explicit AI_Component(entID eid) : Component_t(eid) { }

    std::vector<fixed_vec2> target_vec { fixed_vec2 { -300, -300 }, fixed_vec2 {  200, -300 }
                                       , fixed_vec2 {  200,  200 }, fixed_vec2 { -300,  200 } };
    uint32_t target_index { 0u };

};

} //NS