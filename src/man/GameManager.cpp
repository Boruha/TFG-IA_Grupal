#include <man/GameManager.hpp>
#include <utils/GameConstants.hpp>

namespace AIP {


GameManager::GameManager() {
    systems.emplace_back( std::make_unique<AIP::RenderSystem>( WINDOW_W, WINDOW_H ) );
}

GameManager::~GameManager() {
    systems.clear();
}

bool
GameManager::update(){
    for(auto& sys : systems){
        if(!sys->update())
            return false;
    }
    return true;
}

} //NM