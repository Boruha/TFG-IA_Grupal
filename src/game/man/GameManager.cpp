#include <game/man/GameManager.hpp>
#include <game/utils/ScreenData.hpp>

#include <ecs/ent/Entity_t.hpp>

#include <iostream>
#include <algorithm>

namespace AIP {

GameManager::GameManager() {
    units_man.init();
}

bool
GameManager::update() noexcept {
    render.update(units_man, DeltaTime);
    
    if( !input.update(units_man, DeltaTime) )
        return false;

    ia.update(units_man, DeltaTime);
    movement.update(units_man, DeltaTime);
    collision.update(units_man, DeltaTime);

    if( !attack.update(units_man, DeltaTime) )
        return false;

    checkFpsMsg();

    return true;
}

void
GameManager::checkFpsMsg() noexcept {
    auto& msgs = ia.fps_msg;
    
    while (!msgs.empty()) {
        auto& last_msg = msgs.back();
        
        switch (last_msg.Target) {
        case FPS_Opc::LoopTime : changeLoopTime(last_msg.Action);
            break;
        
        case FPS_Opc::DeltaTime : changeDeltaTime(last_msg.Action);
            break;
        
        case FPS_Opc::Both : changeLoopTime(last_msg.Action);
                             changeDeltaTime(last_msg.Action);
            break;
                
        default:
            break;
        }
        msgs.pop_back();
    }  
}

fint_t<int64_t>
GameManager::getLoopTime() noexcept {
    return LoopTime;
}

fint_t<int64_t>
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
GameManager::changeLoopTime(bool operation) noexcept {
    FPS_LT = (operation) ? FPS_LT * 2.f : FPS_LT / 2.f;
    std::clamp(FPS_LT, 15.f, 120.f);
    LoopTime = setLoopTime();
    std::cout << "El LoopRate es:       " << FPS_LT << "\n";
    std::cout << "Con un Tick size de : " << LoopTime.number << "\n\n";
}

void
GameManager::changeDeltaTime(bool operation) noexcept {
    FPS_DT = (operation) ? FPS_DT * 2.f : FPS_DT / 2.f;
    std::clamp(FPS_DT, 15.f, 120.f);
    DeltaTime = setDeltaTime();
    std::cout << "El DeltaRate es:      " << FPS_DT << "\n";
    std::cout << "Con un Tick size de : " << DeltaTime.number << "\n\n";
}


} //NM