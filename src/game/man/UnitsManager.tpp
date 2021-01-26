#include <game/man/UnitsManager.hpp>
#include <game/utils/fvec2.tpp>

#include <algorithm>
#include <iostream>
#include <utility>

namespace AIP {

inline void
UnitsManager::init() noexcept {
    enemies_vec.reserve(21);

    createPlayerPointer(20, 400l, 400l, Color::Green);
    
    createSoldier(20,  30l,  30l, Color::Red, false);
    createSoldier(20,  60l, -10l, Color::Red, false);
    createSoldier(20, -10l,  20l, Color::Red, false);
    createSoldier(20, -60l,  10l, Color::Red, false);
    createSoldier(20, -20l, -40l, Color::Red, false);

    createSoldier(20, 380l, 400l, Color::Blue, true);
    createSoldier(20, 400l, 420l, Color::Blue, true);
    createSoldier(20, 380l, 420l, Color::Blue, true);
    createSoldier(20, 400l, 380l, Color::Blue, true);
    createSoldier(20, 350l, 380l, Color::Blue, true);
    createSoldier(20, 450l, 380l, Color::Blue, true);
}

inline void
UnitsManager::clear() noexcept {
    ent_man.clear();
    enemies_vec.clear();
    allies_vec.clear();    
    player_id = 0u;
}

/* CREATES & DELETE */
inline void
UnitsManager::createSoldier(const uint32_t size, const int64_t pos_x, const int64_t pos_y, const Color col, bool team) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    if(team)
        allies_vec.push_back(new_ent);
    else    
        enemies_vec.push_back(new_ent);

    ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y }    ) );
    ent_man.addComponentToEntity( new_ent, RenderComponent(   new_ent,    size  ,  size   , col) );
    ent_man.addComponentToEntity( new_ent, CombatComponent(   new_ent ) );
    ent_man.addComponentToEntity( new_ent, AI_Component(      new_ent ) );
}

inline void
UnitsManager::createPlayerPointer(const uint32_t size, const int64_t pos_x, const int64_t pos_y, const Color col) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y }     ) );
    ent_man.addComponentToEntity( new_ent, RenderComponent(   new_ent, { size } , { size }, col ) );
    ent_man.addComponentToEntity( new_ent, InputComponent(    new_ent ) );

    player_id = new_ent;
}

inline void 
UnitsManager::deleteEntity(BECS::entID eid) noexcept { //Bastante fe00 por tu parte
    auto it = std::find_if(enemies_vec.begin(), enemies_vec.end(), [&](BECS::entID id) {
                  return id == eid;
              });

    if(it != enemies_vec.end() ) {
        enemies_vec.erase(it);
        ent_man.deleteEntity(eid);
        return;
    }
    
    it = std::find_if(allies_vec.begin(), allies_vec.end(), [&](BECS::entID id) {
             return id == eid;
         });
              
    if(it != allies_vec.end() ) {
        allies_vec.erase(it);
        ent_man.deleteEntity(eid);
    }
}


/* GETTERS */
template <typename CMP_t> constexpr
std::vector<CMP_t>&
UnitsManager::getComponentVector() noexcept {
    return ent_man.getComponentVector<CMP_t>();
}

template <typename CMP_t> constexpr
CMP_t& 
UnitsManager::getCmpByEntityID(const BECS::entID eid) noexcept {
    return ent_man.getCmpByEntityID<CMP_t>(eid);
}

inline BECS::Entity_t& 
UnitsManager::getEntityByID(BECS::entID eid) noexcept { 
    return ent_man.getEntityByID(eid);
}

inline const BECS::entID  
UnitsManager::getPlayerID() const noexcept { 
    return player_id; 
}  

inline BECS::entID  
UnitsManager::getPlayerID() noexcept { 
    return player_id; 
}

inline constexpr 
std::vector<BECS::entID>& 
UnitsManager::getEnemyIDs() noexcept {
    return enemies_vec;
} 

inline constexpr 
std::vector<BECS::entID>& 
UnitsManager::getAllyIDs() noexcept {
    return allies_vec;
}



} // namespace AIP
