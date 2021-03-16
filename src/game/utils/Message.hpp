#pragma once
#include <game/cmp/AI_Component.hpp>

#include <ecs/utils/Alias.hpp>

namespace AIP {

//enum class FPS_Opc : uint32_t {
//    DeltaTime = 1u,
//    LoopTime  = 2u,
//    Both      = 3u
//};

//struct FPS_Message {
//    constexpr explicit FPS_Message(FPS_Opc target, bool action) 
//        : Target(target), Action(action) { }
//
//    FPS_Opc Target { FPS_Opc::Both };
//    bool    Action { true }; //true = inc, false = dec 
//};

struct AttackMessage {
    constexpr explicit AttackMessage(BECS::entID eid1, BECS::entID eid2, int64_t size) 
        : eid_deal(eid1), eid_damaged(eid2), amount(size) { }

    BECS::entID eid_deal    { 0u };
    BECS::entID eid_damaged { 0u };
    int64_t     amount      { 0  };
};

struct DeathMessage {
    constexpr explicit DeathMessage(BECS::entID id)
        : eid(id) { }

    BECS::entID eid { 0u };
};

struct ComandMessage {
    constexpr explicit ComandMessage(AI_behaviour status) 
        : action(status) { }

    AI_behaviour action { AI_behaviour::no_b };
};


} // NS
