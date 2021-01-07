#pragma once
#include <ecs/cmp/Component_t.hpp>
#include <ecs/utils/Alias.hpp>

#include <vector>

namespace BECS {

struct Entity_t{
    explicit Entity_t();

    void                    addComponent(cmpTypeID cmpType)       noexcept;
    std::vector<cmpTypeID>& getComponentsType()                   noexcept;
    const entID             getID()                         const noexcept;

private:
    inline static entID counterID  { 0u };
    const         entID ent_id     { 0u };

    std::vector<cmpTypeID> cmp_types;
};

} // NS