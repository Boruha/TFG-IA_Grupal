#include <man/GameManager.hpp>
#include <man/Manager_t.hpp>
#include <man/EntityManager.hpp>

#include <utils/GameConstants.hpp>

#include <ent/Entity_t.hpp>

#include <sys/RenderSystem.hpp>
#include <sys/MovementSystem.hpp>

namespace AIP {

GameManager::GameManager() {
    systems.emplace_back( std::make_unique<RenderSystem>( WINDOW_W, WINDOW_H ) );
    systems.emplace_back( std::make_unique<MovementSystem>() );
    
    manager = std::make_unique<EntityManager>();
}

GameManager::~GameManager() {
    systems.clear();
    manager.~unique_ptr();
}

bool
GameManager::update(){
    for(auto& sys : systems){
        if(!sys->update(manager))
            return false;
    }
    return true;
}

} //NM