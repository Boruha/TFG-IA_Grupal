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
#include <game/man/UnitsManager.tpp>
#include <game/sys/SysIncludeList.hpp>
#include <game/utils/fint_t.hpp>
#include <game/utils/GameConditions.hpp>

#include <vector>
#include <memory>

namespace AIP {

struct GameManager {
    explicit GameManager();

    GameManager(const GameManager& )            = delete;
    GameManager(const GameManager&&)            = delete;
    GameManager& operator=(const GameManager& ) = delete;
    GameManager& operator=(const GameManager&&) = delete;

    void             init()         noexcept;
    void             clear()        noexcept;
    GameConditions   update()       noexcept;
    fint_t<int64_t>& getLoopTime()  noexcept;
    fint_t<int64_t>& getDeltaTime() noexcept;


    void loadNextLevel() noexcept;
    void loadLevel0()    noexcept;
    void loadLevel1()    noexcept;

    GameConditions result { GameConditions::Loop };

private:
    UnitsManager units_man;

    RenderSystem<UnitsManager>     render_sys { WIN_W, WIN_H }; //aqui se crea la ventana de openGL/GLFW
    InputSystem<UnitsManager>      input_sys;                   //por lo que todos los cambios relacionados tienen                                                                                  
    AI_System<UnitsManager>        ia_sys;                      //ir a posteriori. Ejemplo, el input.
    MovementSystem<UnitsManager>   movement_sys;
    CollisionSystem<UnitsManager>  collision_sys;
    AttackSystem<UnitsManager>     attack_sys;
    CooldownSystem<UnitsManager>   cd_sys;
    DeathSystem<UnitsManager>      death_sys;
    BulletLifeSystem<UnitsManager> bulletLife_sys;

    int32_t        level_index { 0 };

    fint_t<int64_t> setLoopTime()     noexcept;
    fint_t<int64_t> setDeltaTime()    noexcept;
    void            checkFps()        noexcept;   
    void            changeLoopTime(InterfaceControl& control)  noexcept;
    void            changeDeltaTime(InterfaceControl& control) noexcept;
    
    //TimeInfo
    float           FPS_LT      { 60.f };
    float           FPS_DT      { 60.f };
    const float     Micro_multi { 1000000.f };
    fint_t<int64_t> LoopTime    { setLoopTime()  };
    fint_t<int64_t> DeltaTime   { setDeltaTime() };
};

}
