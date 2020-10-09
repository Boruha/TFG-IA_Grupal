#include <man/GameManager.hpp>

#include <man/Manager_t.hpp>
#include <man/EntityManager.hpp>
#include <utils/GameConstants.hpp>
#include <ent/Entity_t.hpp>
#include <sys/SysIncludeList.hpp>

namespace AIP {

GameManager::GameManager() {
    systems.reserve(5);

    systems.emplace_back( std::make_unique<MovementSystem>() );
    systems.emplace_back( std::make_unique<CollisionSystem>() );
    systems.emplace_back( std::make_unique<RenderSystem>( WINDOW_W, WINDOW_H ) );
    
    manager = std::make_unique<EntityManager>();
}

GameManager::~GameManager() {
    systems.clear();
    manager.~unique_ptr();
}

bool
GameManager::update() noexcept {
    for(auto& sys : systems){
        if(!sys->update(manager, DeltaTime))
            return false;
    }
    return true;
}

} //NM