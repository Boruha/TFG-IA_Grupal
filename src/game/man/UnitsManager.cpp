#include <game/man/UnitsManager.hpp>

#include <algorithm>

namespace AIP {

void
UnitsManager::init() noexcept {
    createSoldier(ufixed64_t(20ul), fixed64_t(30l), fixed64_t(30l), Color::White);
    createSoldier(ufixed64_t(20ul), fixed64_t(60l), fixed64_t(-10l), Color::White);
    createSoldier(ufixed64_t(20ul), fixed64_t(-10l), fixed64_t(20l), Color::White);

    //createSoldier(ufixed64_t(20ul), fixed64_t(-60l), fixed64_t(10l), Color::White);
    //createSoldier(ufixed64_t(20ul), fixed64_t(-20l), fixed64_t(-40l), Color::White);
    
    createPlayer(ufixed64_t(20ul), fixed64_t(200l), fixed64_t(200l), Color::Blue);
}

void
UnitsManager::createSoldier(const ufixed64_t& size, const fixed64_t& pos_x, const fixed64_t& pos_y, const Color col) noexcept {
    auto& new_ent = ent_man.createEntity_t();
        //-> auto eid = entityMan.createEntity_t();

    ent_man.addComponentToEntity( MovementComponent( new_ent.getID(), pos_x, pos_y   ) , new_ent.getID() );
    ent_man.addComponentToEntity( RenderComponent(   new_ent.getID(), size, size, col) , new_ent.getID() );
    ent_man.addComponentToEntity( CombatComponent(   new_ent.getID() )                 , new_ent.getID() );
    ent_man.addComponentToEntity( AI_Component(      new_ent.getID() )                 , new_ent.getID() );
        //-> entityMan.addCmpToEntity( eid, MovementComponent(new_ent.getID(), pos_x, pos_y) );
}

void
UnitsManager::createPlayer(const ufixed64_t& size, const fixed64_t& pos_x, const fixed64_t& pos_y, const Color col) noexcept {
    auto& new_ent = ent_man.createEntity_t();
        //-> auto eid = entityMan.createEntity_t();

    ent_man.addComponentToEntity( MovementComponent( new_ent.getID(), pos_x, pos_y    ) , new_ent.getID() );
    ent_man.addComponentToEntity( RenderComponent(   new_ent.getID(), size, size, col ) , new_ent.getID() );
    ent_man.addComponentToEntity( CombatComponent(   new_ent.getID() )                  , new_ent.getID() );
    ent_man.addComponentToEntity( InputComponent(    new_ent.getID() )                  , new_ent.getID() );
        //-> entityMan.addCmpToEntity( eid, MovementComponent(new_ent.getID(), pos_x, pos_y) );
    player_id = new_ent.getID();
}


} // namespace AIP
