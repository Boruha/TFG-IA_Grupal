#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <game/utils/Patrol_t.hpp>
#include <game/utils/AI_behaviours.hpp>

#include <vector>

namespace AIP {

struct AI_Component : BECS::Component_t {
    explicit AI_Component(BECS::entID eid, Patrol_t::iterator patIt = { }) 
        : Component_t(eid), patrolIt(patIt), target_pos( *patIt ) { }

    Patrol_t::iterator     patrolIt         { };
    AI_behaviour           current_behavior { AI_behaviour::no_b };
    fvec2<fint_t<int64_t>> target_pos       { };
    BECS::entID            target_ent       { 0u };
};

} //NS