#pragma once
#include <game/utils/Message.hpp>

#include <vector>

namespace AIP {

struct Context_t;

struct EventHandler {
    virtual ~EventHandler() = default;
    
    inline static std::vector<FPS_Message>   fps_msg;
    inline static std::vector<AttackMessage> attack_msg;
};

}