#include <man/ComponentStorage.hpp>

namespace AIP {

template<typename T> constexpr 
T& 
ComponentStorage::createComponent(const T&& new_cmp) noexcept {
    auto&  cmp_vec_ref = getCmpCollection<T>();
    return cmp_vec_ref.emplace_back( new_cmp );
}

template<typename T> constexpr 
std::vector<T>& 
ComponentStorage::getCmpCollection() noexcept {
    const auto it = cmp_map.find(Component_t::getCmpTypeID<T>());

    if(it != end(cmp_map))
        return static_cast<CmpVector<T>*>( it->second.get() )->cmps;

    else {
        auto& new_vec = cmp_map[Component_t::getCmpTypeID<T>()] = std::make_unique<CmpVector<T>>();
        return static_cast<CmpVector<T>*>( new_vec.get() )->cmps;
    }
}

template<typename T> constexpr 
const std::vector<T>& 
ComponentStorage::getCmpCollection() const noexcept {
    return const_cast< const std::vector<T>& >( const_cast<ComponentStorage*>(this)->getCmpCollection<T>() );
}

inline Component_t* 
ComponentStorage::deleteCmpByTypeIDAndEntityID(cmpTypeID cid, entID eid) {
    auto it = cmp_map.find(cid);

    if(it == cmp_map.end()) return nullptr; //BAD D D D D

    return it->second->deleteCmpByEntityID(eid);
}

}
