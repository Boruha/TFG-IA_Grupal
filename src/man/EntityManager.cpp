#include <man/EntityManager.hpp>

#include <algorithm>

namespace AIP {

constexpr const std::size_t MAX_ENTITIES { 10u };

//revisar método
EntityManager::EntityManager() {
    ent_map.reserve(MAX_ENTITIES);
    init();
}

void
EntityManager::init() noexcept {
    /*ent 1*/
    createSoldier(ufixed64_t(20ul), fixed64_t(30l), fixed64_t(30l), Color::White);
    /*ent 2*/
    createSoldier(ufixed64_t(20ul), fixed64_t(60l), fixed64_t(-10l), Color::White);
    /*ent 3*/
    createSoldier(ufixed64_t(20ul), fixed64_t(-10l), fixed64_t(20l), Color::White);
    /*ent 4*/
    //createSoldier(ufixed64_t(20ul), fixed64_t(-60l), fixed64_t(10l), Color::White);
    /*ent 5*/
    //createSoldier(ufixed64_t(20ul), fixed64_t(-20l), fixed64_t(-40l), Color::White);

    /*player*/
    auto& ent5  = createEntity_t();
    auto& mov_5 = cmp_storage.createComponent( MovementComponent(ent5.getID(), fixed64_t(200l) , fixed64_t(200l)) );
    auto& ren_5 = cmp_storage.createComponent( RenderComponent(ent5.getID(), ufixed64_t(20ul), ufixed64_t(20ul), Color::Blue) );
    auto& in_5  = cmp_storage.createComponent( InputComponent(ent5.getID()) );
    auto& combat_5  = cmp_storage.createComponent( CombatComponent(ent5.getID()) );

    ent5.addComponent(&mov_5);
    ent5.addComponent(&ren_5);
    ent5.addComponent(&in_5);
    ent5.addComponent(&combat_5);

    player_id = ent5.getID();

}

Entity_t&
EntityManager::createEntity_t() noexcept {
    Entity_t new_ent { };
    auto new_insert_it = ent_map.insert(std::make_pair( new_ent.getID(), new_ent ) );
    //return ent_map[new_ent.getID()] = std::move(new_ent);
    return new_insert_it.first->second;
}

void
EntityManager::createSoldier(const ufixed64_t& size, const fixed64_t& pos_x, const fixed64_t& pos_y, const Color col) noexcept {
    auto& new_ent = createEntity_t();
    auto& mov_cmp = cmp_storage.createComponent( MovementComponent(new_ent.getID(), pos_x, pos_y) );
    auto& ren_cmp = cmp_storage.createComponent( RenderComponent(new_ent.getID(), size, size, col) );
    auto& ai_cmp  = cmp_storage.createComponent( AI_Component(new_ent.getID()) );
    auto& combat_cmp  = cmp_storage.createComponent( CombatComponent(new_ent.getID()) );

    new_ent.addComponent(&mov_cmp);
    new_ent.addComponent(&ren_cmp);
    new_ent.addComponent(&ai_cmp);
    new_ent.addComponent(&combat_cmp);
}

void 
EntityManager::deleteEntity(entID eid) noexcept {
    //Seleccionar entidad.
    if(ent_map.empty()) return;

    auto& ent = getEntityByID(eid);

    //Eliminar sus cmps mediante CmpStorage.
    for(auto& cmp : ent) {
        auto* cmp_ptr = cmp_storage.deleteCmpByTypeIDAndEntityID(cmp.first , eid);
        auto& ent_changed = getEntityByID( cmp_ptr->getEntityID() );
        ent_changed.updateComponent(cmp.first, cmp_ptr);
    }

    //Eliminar entidad.
    auto it_ent = std::find_if( ent_map.begin(), ent_map.end(), 
            [&](const auto& e) { return e.second.getID() == eid; } );
    
    ent_map.erase(it_ent);

    std::cout << "Eliminada entidad: " << eid << "\n";

    //Ajustar los Cmps de las demas entidades 
        //No se queja por el uso de unique_ptr??
}

} // namespace AIP
