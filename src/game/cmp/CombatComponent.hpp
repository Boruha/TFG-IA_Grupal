#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <game/utils/fint_t.hpp>

namespace AIP {

struct CombatComponent : BECS::Component_t {
    explicit CombatComponent(const BECS::entID entityID) : Component_t(entityID) { }

    int64_t         health            { 10 }; //cantidad de dmg que aguante
    int64_t         damage            { 4  }; //cantidad que dmg que inflinge
    fint_t<int64_t> attack_cd         { 3l }; //tiempo entre ataques
    fint_t<int64_t> current_attack_cd { 0l }; //tiempo hasta poder atacar
};

}