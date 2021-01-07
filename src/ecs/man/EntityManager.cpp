#include <ecs/man/EntityManager.hpp>

#include <algorithm>

namespace BECS {

constexpr const std::size_t MAX_ENTITIES { 10u };

EntityManager::EntityManager() {
    ent_map.reserve(MAX_ENTITIES);
}

Entity_t&
EntityManager::createEntity_t() noexcept {
    Entity_t new_ent { };
    auto new_insert_it = ent_map.insert( std::make_pair(new_ent.getID(), new_ent) );
    return new_insert_it.first->second;
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
}

} // namespace