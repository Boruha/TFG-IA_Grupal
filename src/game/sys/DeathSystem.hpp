#pragma once
#include <game/utils/fint_t.hpp>
#include <game/utils/GameConditions.hpp>

namespace AIP {

struct AI_Component;
struct EventCmp_t;

template <typename Context_t>
struct DeathSystem {
    GameConditions update(Context_t& context) noexcept;

};

//void dontHitMeImDead(EventCmp_t& eventCmp, const BECS::entID& eid) noexcept;
//void dontTargetMe(std::vector<AI_Component>& ai_vec, const BECS::entID& eid) noexcept;

} // NS