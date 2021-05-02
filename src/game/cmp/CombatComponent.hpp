#pragma once
#include <ecs/cmp/Component_t.hpp>

#include <game/utils/fint_t.hpp>
#include <game/utils/AI_Constants.hpp>

namespace AIP {

enum class Combat_t : uint32_t {
    None    = 0u,
    Soldier = 1u,
    Archer  = 2u
};

struct CombatComponent : BECS::Component_t {
    explicit CombatComponent(const BECS::entID entityID, const Combat_t type_, const bool team_) 
        : Component_t(entityID), type(type_), team(team_) {
            switch (type) {
                case Combat_t::Archer :
                        health        = 7;
                        damage        = 3;
                        attack_cd     = 2l;
                        attack_range  = RANGE_ATK_DIST;
                        attack_range2 = RANGE_ATK_DIST2;
                    break;

                case Combat_t::Soldier :
                        health        = 12;
                        damage        = 3;
                        attack_cd     = 2l;
                        attack_range  = MEELE_ATK_DIST;
                        attack_range2 = MEELE_ATK_DIST2;
                    break;
                case Combat_t::None :
                        //NADA
                    break;
            }
    }

    int64_t         health            { 1l }; //cantidad de dmg que aguante
    int64_t         damage            { 1l }; //cantidad que dmg que inflinge
    fint_t<int64_t> attack_cd         { 1l }; //tiempo entre ataques
    fint_t<int64_t> current_attack_cd { 0l }; //tiempo hasta poder atacar
    fint_t<int64_t> attack_range      { 0l }; //distancia de  atacar
    fint_t<int64_t> attack_range2     { 0l }; //distancia de  atacar al cuadrado
    Combat_t        type              { Combat_t::None };
    bool            team              { false };
};

}