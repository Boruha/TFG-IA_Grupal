#pragma once

#include <ecs/utils/Alias.hpp>

namespace BECS {

struct Component_t {
    explicit Component_t(const entID entityID) : cmp_id(++counterID), ent_id(entityID) { }

    [[nodiscard]] cmpID getComponentID() const { return cmp_id; }
    [[nodiscard]] entID getEntityID()    const { return ent_id; }

    template<typename T>
    static cmpTypeID getCmpTypeID() { 
        static const cmpTypeID type_id { ++counterTypeID };
        return  type_id;
    }

private:
    inline static cmpID     counterID     { 0u };
    inline static cmpTypeID counterTypeID { 0u };
                  cmpID     cmp_id        { 0u };
                  entID     ent_id        { 0u };
};

}
