#include <man/GameManager.hpp>
#include <man/EntityManager.hpp>

#include <ent/Entity_t.hpp>

#include <sys/SysIncludeList.hpp>

#include <utils/ScreenData.hpp>

namespace AIP {

GameManager::GameManager() {
    
    systems.reserve(10);

    systems.emplace_back( std::make_unique<RenderSystem>( WINDOW_W, WINDOW_H ) ); //aqui se crea la ventana de tinyPTC
    systems.emplace_back( std::make_unique<InputSystem>() );                      //por lo que todos los cambios relacionados tienen                                                                                  
    systems.emplace_back( std::make_unique<AI_System>() );                        //ir a posteriori. Ejemplo, los callbacks del input.
    systems.emplace_back( std::make_unique<MovementSystem>() );
    systems.emplace_back( std::make_unique<CollisionSystem>() );
    manager = std::make_unique<EntityManager>();
}

bool
GameManager::update() noexcept {
    for(auto& sys : systems){
        if(!sys->update(manager, DeltaTime))
            return false;
    }
    return true;
}

fixed64_t
GameManager::getLoopTime() noexcept {
    return LoopTime;
}

fixed64_t
GameManager::getDeltaTime() noexcept {
    return DeltaTime;
}

fixed64_t
GameManager::setLoopTime() noexcept {
    return fixed64_t { ((1.f / FPS_LT) * Micro_multi) / SCALE_S };
}

fixed64_t
GameManager::setDeltaTime() noexcept {
    return fixed64_t { 1.f / FPS_DT };
}

void
GameManager::doubleLoopTime() noexcept {
    FPS_LT *= 2.f;
    LoopTime = setLoopTime();
}

void
GameManager::halfLoopTime() noexcept {
    FPS_LT /= 2.f;
    LoopTime = setLoopTime();
}

void
GameManager::doubleDeltaTime() noexcept {
    FPS_DT *= 2.f;
    DeltaTime = setDeltaTime();
}

void
GameManager::halfDeltaTime() noexcept {
    FPS_DT /= 2.f;
    DeltaTime = setDeltaTime();
}


} //NM