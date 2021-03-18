#pragma once
#include <game/utils/Message.hpp>
#include <queue>

namespace AIP {

struct Context_t;

struct EventHandler {
    virtual ~EventHandler() = default;
    
    inline static std::queue<BulletSpawn>   bullet_msg;
    inline static std::queue<AttackMessage> attack_msg;
    inline static std::queue<ComandMessage> comand_msg;
    inline static std::queue<DeathMessage>  death_msg;
};

}