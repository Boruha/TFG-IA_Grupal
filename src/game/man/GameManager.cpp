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

#include <game/man/GameManager.hpp>
#include <game/utils/ScreenData.hpp>

#include <ecs/ent/Entity_t.hpp>

#include <iostream>
#include <algorithm>

namespace AIP {

GameManager::GameManager() {
    loadLevel0();
}

void
GameManager::init() noexcept {
    FPS_LT      = 60.f;
    FPS_DT      = 60.f;
    LoopTime    = setLoopTime();
    DeltaTime   = setDeltaTime();
    units_man.init();
    render_sys.debug_mode = false; //un poco feo pero bueno.
}

void
GameManager::loadNextLevel() noexcept {
    level_index = (level_index + 1) % 2;
    
    switch (level_index) {
        case 0: loadLevel0();
            break;

        case 1: loadLevel1();
            break;
    }  
}


void
GameManager::loadLevel0() noexcept {
    level_index = 0;
    units_man.loadLevel0();
}

void
GameManager::loadLevel1() noexcept {
    level_index = 1;
    units_man.loadLevel1();
}

void
GameManager::clear() noexcept {
    units_man.clear();
}

GameConditions
GameManager::update() noexcept {
    auto loopResult { GameConditions::Loop };

    //timers and dmg
    cd_sys.update(units_man, DeltaTime);
    //pj decision
    if( !input_sys.update(units_man) )
        return GameConditions::Cerrar;

    //ia decision
    ia_sys.update(units_man, DeltaTime);
    //physics
    movement_sys.update(units_man, DeltaTime);

    loopResult     = collision_sys.update(units_man);
    if(loopResult != GameConditions::Loop)
        result     = loopResult;

    //draw
    if( render_sys.update(units_man) )
        return GameConditions::Cerrar;

    checkFps();
 
    //deleted entities
    bulletLife_sys.update(units_man);

    loopResult     = death_sys.update(units_man);
    if(loopResult != GameConditions::Loop)
        result     = loopResult;

    attack_sys.update(units_man);
 
    return result;
}

void
GameManager::checkFps() noexcept {
    auto& control = units_man.getSCmpByType<InterfaceControl>();

    if(control.changed) {
        changeLoopTime(control);
        changeDeltaTime(control);
        control.changed = false;
    }
}

fint_t<int64_t>&
GameManager::getLoopTime() noexcept {
    return LoopTime;
}

fint_t<int64_t>&
GameManager::getDeltaTime() noexcept {
    return DeltaTime;
}

fint_t<int64_t>
GameManager::setLoopTime() noexcept {
    return fint_t<int64_t> { ((1.f / FPS_LT) * Micro_multi) / fint_t<int64_t>::SCALE };
}

fint_t<int64_t>
GameManager::setDeltaTime() noexcept {
    return fint_t<int64_t> { 1.f / FPS_DT };
}

void
GameManager::changeLoopTime(InterfaceControl& control) noexcept {        
    FPS_LT = control.deltaSize;
    std::clamp(FPS_LT, 1.f, 120.f);

    LoopTime = setLoopTime();
}

void
GameManager::changeDeltaTime(InterfaceControl& control) noexcept {    
    FPS_DT = control.deltaTime;
    std::clamp(FPS_DT, 1.f, 120.f);

    DeltaTime = setDeltaTime();
}


} //NM