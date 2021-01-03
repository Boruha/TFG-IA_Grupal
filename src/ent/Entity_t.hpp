#pragma once
#include <unordered_map>

#include <utils/Alias.hpp>
#include <cmp/Component_t.hpp>


namespace AIP {

struct Entity_t{
    explicit Entity_t() : ent_id(++counterID) { };

    template<typename T> void 
    constexpr addComponent(T* cmp) {
        my_cmps[Component_t::getCmpTypeID<T>()] = cmp;
    }

    const entID& getID() const { return ent_id; }

    template<typename T> constexpr const T* 
    getComponent() const noexcept {
        T* result     = nullptr;
        const auto it = my_cmps.find(Component_t::getCmpTypeID<T>());
        
        if(it != cend(my_cmps))
            result = static_cast<T*>(it->second);

        return result;
    }

    template<typename T> T* 
    getComponent() noexcept {
        return const_cast<T*>( const_cast<const Entity_t*>(this)->getComponent<T>() );
    }

    auto begin() { return my_cmps.begin(); }
    auto end()   { return my_cmps.end();   }

private:
    inline static entID counterID  { 0u };
    const         entID ent_id     { 0u };
    std::unordered_map<cmpTypeID, Component_t*> my_cmps;
};

} // NS