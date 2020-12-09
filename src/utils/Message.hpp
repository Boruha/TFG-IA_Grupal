#pragma once

#include <cstdint>

namespace AIP {

enum class FPS_Opc : uint32_t {
    DeltaTime = 1u,
    LoopTime  = 2u,
    Both      = 3u
};

struct FPS_Message {
    constexpr explicit FPS_Message(FPS_Opc target, bool action) : Target(target), Action(action) { }

    FPS_Opc Target { FPS_Opc::Both };
    bool    Action { true }; //true = inc, false = dec 
};

} // NS
