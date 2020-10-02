#include <man/GameManager.hpp>

#include <utils/GameConstants.hpp>
#include <ent/Entity_t.hpp>
#include <man/EntityManager.hpp>

namespace AIP {

GameManager::GameManager() {
    systems.emplace_back( std::make_unique<AIP::RenderSystem>( WINDOW_W, WINDOW_H ) );
    manager = std::make_unique<EntityManager>();
}

GameManager::~GameManager() {
    systems.clear();
}

const std::vector<std::unique_ptr<Entity_t>>&  
GameManager::getEntities() const {
    std::vector<std::unique_ptr<Entity_t>> vec { };
    return vec;
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