#include <ecs/man/ComponentStorage.hpp>

#include <cstdlib>

namespace BECS {

template<typename T> constexpr 
T& 
ComponentStorage::createComponent(const T& new_cmp) noexcept {
    auto&  cmp_vec_ref = getCmpCollection<T>();
    return cmp_vec_ref.emplace_back( new_cmp );
}

template<typename T> constexpr 
std::vector<T>&
ComponentStorage::getCmpCollection() noexcept {
    opt_refw<std::vector<T>> result { };
    auto it = cmp_map.find(Component_t::getCmpTypeID<T>());

    if(it != end(cmp_map))
        result = static_cast<CmpVector<T>*>( it->second.get() )->cmps;

    else {
        auto& new_vec = cmp_map[Component_t::getCmpTypeID<T>()] = std::make_unique<CmpVector<T>>();
        result        = static_cast<CmpVector<T>*>( new_vec.get() )->cmps;
    }

    return (*result).get();
}

/*template<typename T> constexpr //CHANGE THIS
const std::vector<T>&
ComponentStorage::getCmpCollection() const noexcept {
    return const_cast< const std::vector<T>& >( const_cast<ComponentStorage*>(this)->getCmpCollection<T>() );
}*/

template<typename T> constexpr
T& 
ComponentStorage::getCmpByEntityID(const entID eid) noexcept {
    auto& cmp_vec_ref = getCmpCollection<T>();

    auto it_cmp = std::find_if(cmp_vec_ref.begin(), cmp_vec_ref.end(),
            [&eid](T& cmp) {
                return cmp.getEntityID() == eid;
            }
        );

    if( it_cmp == cmp_vec_ref.end() )
        std::exit(EXIT_FAILURE);

    return *it_cmp; //vec_iterator *-> cmp
}

inline bool 
ComponentStorage::deleteCmpByTypeIDAndEntityID(cmpTypeID cid, entID eid) noexcept {
    auto result = true;
    auto it     = cmp_map.find(cid);

    if(it == cmp_map.end())
        result = false;
    else
        result = it->second->deleteCmpByEntityID(eid);

    return result;
}

}
