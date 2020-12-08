#include <man/GameManager.hpp>
#include <man/EntityManager.hpp>

#include <ent/Entity_t.hpp>

#include <sys/SysIncludeList.hpp>

#include <utils/ScreenData.hpp>
#include <utils/TimeData.hpp>

namespace AIP {

GameManager::GameManager() {
    
    systems.reserve(10);

    systems.emplace_back( std::make_unique<AI_System>() );
    systems.emplace_back( std::make_unique<MovementSystem>() );
    systems.emplace_back( std::make_unique<CollisionSystem>() );
    systems.emplace_back( std::make_unique<RenderSystem>( WINDOW_W, WINDOW_H ) ); //aqui se crea la ventana de tinyPTC
    systems.emplace_back( std::make_unique<InputSystem>() );                      //por lo que todos los cambios relacionados tienen
                                                                                  //ir a posteriori. Ejemplo, los callbacks del input.
    manager = std::make_unique<EntityManager>();
}

bool
GameManager::update() noexcept {
    for(auto& sys : systems){
        if(!sys->update(manager, DELTA_TIME))
            return false;
    }
    return true;
}

} //NM