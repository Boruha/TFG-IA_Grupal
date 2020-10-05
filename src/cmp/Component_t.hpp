#pragma once
#include <utils/Alias.hpp>

namespace AIP {

struct Component_t {
    explicit Component_t(const entID entityID) : cmp_id(++counterID), ent_id(entityID) { }

    [[nodiscard]] const cmpID& getComponentID() const { return cmp_id; }
    [[nodiscard]] const entID& getEntityID()    const { return ent_id; }

    template<typename T> //constexpr(?)
    static decltype(auto) getCmpTypeID() { 
        static const cmpTypeID type_id { ++counterTypeID };
        return  type_id;
    }

private:
    inline static cmpID     counterID     { 0 };
    inline static cmpTypeID counterTypeID { 0 };
    const         cmpID     cmp_id        { 0 };
    const         entID     ent_id        { 0 };
};

}
