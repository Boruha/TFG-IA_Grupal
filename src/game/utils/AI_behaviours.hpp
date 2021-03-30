#pragma once
#include <cstdint>

namespace AIP {

enum class AI_behaviour : uint16_t {
    no_b     = 0u,
    patrol_b = 1u,
    chase_b  = 2u,
    attack_b = 4u,
    follow_b = 5u
};

};