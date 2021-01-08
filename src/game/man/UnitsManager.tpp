#include <game/man/UnitsManager.hpp>
#include <game/utils/fint_t.tpp>

#include <algorithm>
#include <iostream>
#include <utility>

namespace AIP {

inline void
UnitsManager::init() noexcept {



    createSoldier(ufixed64_t(20ul), fixed64_t(30l), fixed64_t(30l), Color::White); //(?) pasar tipos básicos y que se creen dentro?
    createSoldier(ufixed64_t(20ul), fixed64_t(60l), fixed64_t(-10l), Color::White);
    createSoldier(ufixed64_t(20ul), fixed64_t(-10l), fixed64_t(20l), Color::White);

    //createSoldier(ufixed64_t(20ul), fixed64_t(-60l), fixed64_t(10l), Color::White);
    //createSoldier(ufixed64_t(20ul), fixed64_t(-20l), fixed64_t(-40l), Color::White);
    
    createPlayer(ufixed64_t(20ul), fixed64_t(200l), fixed64_t(200l), Color::Blue);
}

/* CREATES & DELETE */
inline void
UnitsManager::createSoldier(const ufixed64_t& size, const fixed64_t& pos_x, const fixed64_t& pos_y, const Color col) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    ent_man.addComponentToEntity( MovementComponent( new_ent, pos_x, pos_y   ) , new_ent );
    ent_man.addComponentToEntity( RenderComponent(   new_ent, size, size, col) , new_ent );
    ent_man.addComponentToEntity( CombatComponent(   new_ent )                 , new_ent );
    ent_man.addComponentToEntity( AI_Component(      new_ent )                 , new_ent );
}

inline void
UnitsManager::createPlayer(const ufixed64_t& size, const fixed64_t& pos_x, const fixed64_t& pos_y, const Color col) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    ent_man.addComponentToEntity( MovementComponent( new_ent, pos_x, pos_y    ) , new_ent );
    ent_man.addComponentToEntity( RenderComponent(   new_ent, size, size, col ) , new_ent );
    ent_man.addComponentToEntity( CombatComponent(   new_ent )                  , new_ent );
    ent_man.addComponentToEntity( InputComponent(    new_ent )                  , new_ent );

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
