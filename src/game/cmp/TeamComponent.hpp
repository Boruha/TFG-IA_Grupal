#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <game/utils/AI_behaviours.hpp>

#include <cstdint>

namespace AIP {

enum class Formation : uint16_t {
    no_form     = 0u,
    ring_form   = 1u
};

struct TeamComponent : BECS::Component_t {
    explicit TeamComponent(const BECS::entID entityID) : Component_t(entityID) { }

    Formation    current_form { Formation::no_form };
    AI_behaviour action       { AI_behaviour::no_b };
};

}