#pragma once
#include <game/utils/fvec2.hpp>

#include <ecs/utils/Alias.hpp>
#include <game/utils/GameConditions.hpp>

#include <vector>

namespace AIP {

struct MovementComponent;

template <typename Context_t>
struct CollisionSystem {
    GameConditions update(Context_t& context) noexcept;

private:
    GameConditions checkTriggerBoxes(Context_t& context) noexcept; 

    void checkWorldLimits(Context_t& context, std::vector<MovementComponent>& movCmps) noexcept;
    void bulletsCollision(Context_t& context, std::vector<BECS::entID>& team, std::vector<BECS::entID>& bullets) noexcept;
};

} // NS
