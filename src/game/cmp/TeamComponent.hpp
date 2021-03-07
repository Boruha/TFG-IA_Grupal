#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <cstdint>

namespace AIP {

enum class Formation : uint32_t {
    no_form     = 0u,
    //follow_form = 1u,
    ring_form   = 2u
};

struct TeamComponent : BECS::Component_t {
    explicit TeamComponent(const BECS::entID entityID) : Component_t(entityID) { }

    Formation current_form { Formation::no_form };
};

}