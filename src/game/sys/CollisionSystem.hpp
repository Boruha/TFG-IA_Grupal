#pragma once
#include <game/utils/EventHandler.hpp>
#include <game/utils/fvec2.hpp>

namespace AIP {

template <typename Context_t>
struct CollisionSystem : EventHandler {
    void update(Context_t& context) noexcept;

private:
    void bulletsCollision(Context_t& context, std::vector<BECS::entID>& team, std::vector<BECS::entID>& bullets) noexcept;
};

} // NS
