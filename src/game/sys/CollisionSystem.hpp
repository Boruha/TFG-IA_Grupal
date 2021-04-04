#pragma once
#include <game/utils/fvec2.hpp>

#include <ecs/utils/Alias.hpp>

#include <vector>

namespace AIP {

template <typename Context_t>
struct CollisionSystem {
    void update(Context_t& context) noexcept;

private:
    void bulletsCollision(Context_t& context, std::vector<BECS::entID>& team, std::vector<BECS::entID>& bullets) noexcept;
};

} // NS
