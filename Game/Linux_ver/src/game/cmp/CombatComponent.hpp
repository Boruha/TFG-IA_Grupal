/*
Copyright (C) <2020-2021> Borja Pozo Wals (Tw: @Chico_Riot | GitHub: Boruha)

This file is part of 'TFG: Gestión y manejo de comportamientos grupales 
de entidades en videojuegos'.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
                        health        = 14;
                        damage        = 7;
                        attack_cd     = 3l;
                        attack_range  = RANGE_ATK_DIST;
                        attack_range2 = RANGE_ATK_DIST2;
                    break;

                case Combat_t::Soldier :
                        health        = 24;
                        damage        = 4;
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