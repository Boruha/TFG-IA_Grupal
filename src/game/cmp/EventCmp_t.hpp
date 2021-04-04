#pragma once
#include <game/utils/Message.hpp>
#include <queue>
#include <vector>

namespace AIP {

struct EventCmp_t {
    std::queue<BulletSpawn>    bullet_msg;
    std::vector<AttackMessage> attack_msg;
    std::queue<DeathMessage>   death_msg;
};

}