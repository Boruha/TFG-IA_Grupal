#pragma once
#include <game/man/UnitsManager.tpp>
#include <game/sys/SysIncludeList.hpp>
#include <game/utils/fint_t.hpp>

#include <vector>
#include <memory>

namespace AIP {

struct GameManager {
    explicit GameManager();

    GameManager(const GameManager& )            = delete;
    GameManager(const GameManager&&)            = delete;
    GameManager& operator=(const GameManager& ) = delete;
    GameManager& operator=(const GameManager&&) = delete;

    bool            update()       noexcept;
    fint_t<int64_t> getLoopTime()  noexcept;
    fint_t<int64_t> getDeltaTime() noexcept;

private:
    UnitsManager units_man;

    RenderSystem<UnitsManager>    render { WINDOW_W, WINDOW_H }; //aqui se crea la ventana de tinyPTC
    InputSystem<UnitsManager>     input;                         //por lo que todos los cambios relacionados tienen                                                                                  
    AI_System<UnitsManager>       ia;                            //ir a posteriori. Ejemplo, los callbacks del input.
    MovementSystem<UnitsManager>  movement;
    CollisionSystem<UnitsManager> collision;
    AttackSystem<UnitsManager>    attack;

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
