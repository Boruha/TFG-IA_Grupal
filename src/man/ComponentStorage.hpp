#pragma once

#include <cmp/CmpIncludeList.hpp>

#include <utils/Alias.hpp>
#include <utils/Color.hpp>

#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>

namespace AIP {

//Struct generico para nuestras temp de Cmps
struct CmpCollection {
    virtual ~CmpCollection() = default;
    virtual void deleteCmpByEntityID(entID eid) = 0;
};

//Vector que se creará por cada Cmp
template<typename T>
struct CmpVector : CmpCollection {
    explicit CmpVector<T>() { cmps.reserve(10u); }
    
    void deleteCmpByEntityID(entID eid) override { 
        auto it_cmp = std::find_if(cmps.begin(), cmps.end(), 
            [&eid](std::unique_ptr<T>& cmp) { return cmp->getEntityID() == eid; }
        );

        if( it_cmp == cmps.end() ) return; //MAMAMAMAMAAAL
        cmps.erase(it_cmp);
    }

    std::vector<std::unique_ptr<T>> cmps;
};


struct ComponentStorage {
    explicit ComponentStorage() = default;
             
               ComponentStorage(const ComponentStorage& ) = delete;
               ComponentStorage(const ComponentStorage&&) = delete;
    ComponentStorage& operator=(const ComponentStorage& ) = delete;
    ComponentStorage& operator=(const ComponentStorage&&) = delete;

    template<typename T>
    [[nodiscard]] constexpr std::unique_ptr<T>& 
    createComponent(const T&& new_cmp) noexcept {
        auto&  cmp_vec_ref = getCmpCollection<T>();
        return cmp_vec_ref.emplace_back( std::make_unique<T>(new_cmp) );
    }

    template<typename T>
    [[nodiscard]] constexpr std::vector<std::unique_ptr<T>>& 
    getCmpCollection() noexcept {
        const auto it = cmp_map.find(Component_t::getCmpTypeID<T>());
    
        if(it != end(cmp_map))
            return static_cast<CmpVector<T>*>( it->second.get() )->cmps;

        else {
            auto& new_vec = cmp_map[Component_t::getCmpTypeID<T>()] = std::make_unique<CmpVector<T>>();
            return static_cast<CmpVector<T>*>( new_vec.get() )->cmps;
        }
    }

    void 
    deleteCmpByTypeIDAndEntityID(cmpTypeID cid, entID eid) {
        auto it = cmp_map.find(cid);
        
        if(it == cmp_map.end()) return; //BAD D D D D
        
        it->second->deleteCmpByEntityID(eid);
    }

private:
    std::unordered_map<std::size_t , std::unique_ptr<CmpCollection>> cmp_map;
};

}