#pragma once
#include <unordered_map>

#include <utils/Alias.hpp>
#include <cmp/Component_t.hpp>


namespace AIP {

struct Entity_t{
    explicit Entity_t() : ent_id(++counterID) { };
            ~Entity_t() { my_cmps.clear(); };

    
    template<typename T> void 
    constexpr addComponent(T* cmp) {
        my_cmps[Component_t::getCmpTypeID<T>()] = cmp;
    }

    const entID& getID() const { return ent_id; }

    template<typename T> decltype(auto) 
    constexpr getComponent() const noexcept {
        T* result     = nullptr;
        const auto it = my_cmps.find(Component_t::getCmpTypeID<T>());
        
        if(it != cend(my_cmps))
            result = static_cast<T*>(it->second);

        return result;
    }

    template<typename T> decltype(auto) 
    getComponent() noexcept {
        return const_cast<T*>( std::as_const(*this).getComponent<T>() );
    }


private:
    inline static entID counterID  { 0 };
    const         entID ent_id     { 0 };
    std::unordered_map<cmpID, Component_t*> my_cmps;
};

} // NS