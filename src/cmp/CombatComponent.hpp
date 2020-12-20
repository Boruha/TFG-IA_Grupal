#pragma once
#include <cmp/Component_t.hpp>

#include <utils/Vec2.hpp>

namespace AIP {

struct CombatComponent : Component_t {
    explicit CombatComponent(const entID entityID) : Component_t(entityID) { }

    int64_t   health            { 10 }; //cantidad de dmg que aguante
    int64_t   damage            { 4  }; //cantidad que dmg que inflinge
    fixed64_t attack_cd         { 3l }; //tiempo entre ataques
    fixed64_t current_attack_cd { 0l }; //tiempo hasta poder atacar
};

}