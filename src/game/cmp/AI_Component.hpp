#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <game/utils/fvec2.hpp>

#include <vector>

namespace AIP {

enum class AI_behaviour : uint16_t {
    no_b     = 0u,
    patrol_b = 1u,
    chase_b  = 2u,
    evade_b  = 3u,
    attack_b = 4u,
    follow_b = 5u
};

//hay que pasar el objetivo a un parametro.
//hacerlo flexible para ambos equipos
struct AI_Component : BECS::Component_t {
    explicit AI_Component(BECS::entID eid) : Component_t(eid) { }

    std::vector< fvec2<fint_t<int64_t>> > target_vec { { { -300l }, { -300l } }
                                                     , { {  200l }, { -300l } }
                                                     , { {  200l }, {  200l } }
                                                     , { { -300l }, {  200l } } 
                                                     };
    std::size_t            target_index     { 0u };
    AI_behaviour           current_behavior { AI_behaviour::no_b };
    fvec2<fint_t<int64_t>> target_pos       { target_vec.front() };
    BECS::entID            target_ent       { 0u };
};

} //NS