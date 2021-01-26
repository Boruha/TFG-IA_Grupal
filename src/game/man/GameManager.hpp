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

private:
    UnitsManager units_man;

    RenderSystem<UnitsManager>    render_sys { U_WINDOW_W, U_WINDOW_H }; //aqui se crea la ventana de tinyPTC
    InputSystem<UnitsManager>     input_sys;                             //por lo que todos los cambios relacionados tienen                                                                                  
    AI_System<UnitsManager>       ia_sys;                                //ir a posteriori. Ejemplo, los callbacks del input.
    MovementSystem<UnitsManager>  movement_sys;
    CollisionSystem<UnitsManager> collision_sys;
    AttackSystem<UnitsManager>    attack_sys;
    CooldownSystem<UnitsManager>  cd_sys;
    DeathSystem<UnitsManager>     death_sys;

    GameConditions result { GameConditions::Loop };

    fint_t<int64_t> setLoopTime()                   noexcept;
    fint_t<int64_t> setDeltaTime()                  noexcept;
    void            checkFpsMsg()                   noexcept;   
    void            changeLoopTime(bool operation)  noexcept;
    void            changeDeltaTime(bool operation) noexcept;
    
    //TimeInfo
    float           FPS_LT      { 60.f };
    float           FPS_DT      { 60.f };
    const float     Micro_multi { 1000000.f };
    fint_t<int64_t> LoopTime    { setLoopTime()  };
    fint_t<int64_t> DeltaTime   { setDeltaTime() };
};

}
