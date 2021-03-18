#include <ecs/man/EntityManager.hpp>

#include <algorithm>

namespace BECS {

inline
EntityManager::EntityManager() {
    ent_map.reserve(MAX_ENTITIES);
}

inline void 
EntityManager::clear() noexcept { 
    cmp_storage.clear();
    ent_map.clear();
    ent_map.reserve(MAX_ENTITIES);
}

/* CREATE / DELETE  */
inline const entID
EntityManager::createEntity_t() noexcept {
    Entity_t new_ent { };
    auto new_insert_it = ent_map.insert( std::make_pair(new_ent.getID(), new_ent) );
    return new_insert_it.first->first;
}

template <typename CMP_t>
CMP_t& 
EntityManager::addComponentToEntity(const entID eid, const CMP_t& new_cmp) noexcept {
    auto& ref_cmp = cmp_storage.createComponent(new_cmp);
    auto& ref_ent = getEntityByID(eid);

    ref_ent.addComponent( Component_t::getCmpTypeID<CMP_t>() );
    return ref_cmp;
}

inline void 
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

/* GETTERS  */
inline Entity_t& 
EntityManager::getEntityByID(entID eid) noexcept { 
    return ent_map.at(eid); 
}

template <typename CMP_t> constexpr 
CMP_t& 
EntityManager::getCmpByEntityID(const entID eid) noexcept { 
    return cmp_storage.getCmpByEntityID<CMP_t>(eid); 
}

template <typename CMP_t> constexpr
std::vector<CMP_t>&
EntityManager::getComponentVector() noexcept { 
    return cmp_storage.getCmpCollection<CMP_t>(); 
}


} // namespace