#include <game/man/UnitsManager.hpp>

#include <algorithm>

namespace AIP {

void
UnitsManager::init() noexcept {
    createSoldier(ufixed64_t(20ul), fixed64_t(30l), fixed64_t(30l), Color::White); //(?) pasar tipos básicos y que se creen dentro?
    createSoldier(ufixed64_t(20ul), fixed64_t(60l), fixed64_t(-10l), Color::White);
    createSoldier(ufixed64_t(20ul), fixed64_t(-10l), fixed64_t(20l), Color::White);

    //createSoldier(ufixed64_t(20ul), fixed64_t(-60l), fixed64_t(10l), Color::White);
    //createSoldier(ufixed64_t(20ul), fixed64_t(-20l), fixed64_t(-40l), Color::White);
    
    createPlayer(ufixed64_t(20ul), fixed64_t(200l), fixed64_t(200l), Color::Blue);
}

void
UnitsManager::createSoldier(const ufixed64_t& size, const fixed64_t& pos_x, const fixed64_t& pos_y, const Color col) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    ent_man.addComponentToEntity( MovementComponent( new_ent, pos_x, pos_y   ) , new_ent );
    ent_man.addComponentToEntity( RenderComponent(   new_ent, size, size, col) , new_ent );
    ent_man.addComponentToEntity( CombatComponent(   new_ent )                 , new_ent );
    ent_man.addComponentToEntity( AI_Component(      new_ent )                 , new_ent );
}

void
UnitsManager::createPlayer(const ufixed64_t& size, const fixed64_t& pos_x, const fixed64_t& pos_y, const Color col) noexcept {
    const auto new_ent = ent_man.createEntity_t();

    ent_man.addComponentToEntity( MovementComponent( new_ent, pos_x, pos_y    ) , new_ent );
    ent_man.addComponentToEntity( RenderComponent(   new_ent, size, size, col ) , new_ent );
    ent_man.addComponentToEntity( CombatComponent(   new_ent )                  , new_ent );
    ent_man.addComponentToEntity( InputComponent(    new_ent )                  , new_ent );

    player_id = new_ent;
}


} // namespace AIP
