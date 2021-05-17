#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <game/utils/GameConditions.hpp>

namespace AIP {

struct TriggerCmp_t : BECS::Component_t {
    explicit TriggerCmp_t(const BECS::entID entityID, GameConditions e)
        : Component_t(entityID), event(e) { }
    
    GameConditions event { GameConditions::Loop };
};

}