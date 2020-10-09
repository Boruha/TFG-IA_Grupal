#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <cstdint>

#include <utils/Alias.hpp>
#include <utils/Color.hpp>

#include <cmp/CmpIncludeList.hpp>


namespace AIP {

struct RenderComponent;
struct MovementComponent;

//Struct generico para nuestras temp de Cmps
struct CmpCollection {
    virtual ~CmpCollection() = default;
};

//Vector que se creará por cada Cmp
template<typename T>
struct CmpVector : CmpCollection {
    explicit CmpVector<T>() { cmps.reserve(2); }
    ~CmpVector<T>() override { cmps.clear(); };
    std::vector<std::unique_ptr<T>> cmps;
};


struct ComponentStorage {
    explicit ComponentStorage() = default;
             
               ComponentStorage(const ComponentStorage& ) = delete; //1 '&' = LValue, 2 '&' = RValue (Valor temporal)
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

private:
    std::unordered_map<std::size_t , std::unique_ptr<CmpCollection>> cmp_map;
};

}