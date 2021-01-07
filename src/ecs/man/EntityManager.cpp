#include <ecs/man/EntityManager.hpp>

#include <game/utils/ufixed64_t.hpp>

#include <algorithm>

namespace BECS {

constexpr const std::size_t MAX_ENTITIES { 10u };

EntityManager::EntityManager() {
    ent_map.reserve(MAX_ENTITIES);
}

const entID
EntityManager::createEntity_t() noexcept {
    Entity_t new_ent { };
    auto new_insert_it = ent_map.insert( std::make_pair(new_ent.getID(), new_ent) );
    return new_insert_it.first->first;
}

void 
EntityManager::deleteEntity(entID eid) noexcept {
    if( ent_map.empty() ) return;

    auto& ent       = getEntityByID(eid);
    auto& cmp_types = ent.getComponentsType();

    for(auto type : cmp_types)
        cmp_storage.deleteCmpByTypeIDAndEntityID(type , eid);
    
    auto it_ent = std::find_if( ent_map.begin(), ent_map.end(), 
            [&](const auto& e) { return e.second.getID() == eid; } );
    
    ent_map.erase(it_ent);
}

} // namespace