#include <game/man/UnitsManager.hpp>
#include <game/utils/fvec2.tpp>

#include <algorithm>
#include <iostream>
#include <utility>

namespace AIP {

inline void
UnitsManager::init() noexcept {
    createSoldier(20ul,  30l,  30l, Color::White);
    createSoldier(20ul,  60l, -10l, Color::White);
    createSoldier(20ul, -10l,  20l, Color::White);

    //createSoldier(20ul, -60l, 10l, Color::White);
    //createSoldier(20ul, -20l, -40l, Color::White);
    
    createPlayer(20ul, 200l, 200l, Color::Blue);
}

/* CREATES & DELETE */
inline void
UnitsManager::createSoldier(const uint64_t size, const int64_t pos_x, const int64_t pos_y, const Color col) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y }    ) );
    ent_man.addComponentToEntity( new_ent, RenderComponent(   new_ent, { size } , { size }, col) );
    ent_man.addComponentToEntity( new_ent, CombatComponent(   new_ent ) );
    ent_man.addComponentToEntity( new_ent, AI_Component(      new_ent ) );
}

inline void
UnitsManager::createPlayer(const uint64_t size, const int64_t pos_x, const int64_t pos_y, const Color col) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    ent_man.addComponentToEntity( new_ent, MovementComponent( new_ent, { pos_x }, { pos_y }     ) );
    ent_man.addComponentToEntity( new_ent, RenderComponent(   new_ent, { size } , { size }, col ) );
    ent_man.addComponentToEntity( new_ent, CombatComponent(   new_ent ) );
    ent_man.addComponentToEntity( new_ent, InputComponent(    new_ent ) );

    player_id = new_ent;
}

inline void 
UnitsManager::deleteEntity(BECS::entID eid) noexcept { 
    return ent_man.deleteEntity(eid); 
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


} // namespace AIP
