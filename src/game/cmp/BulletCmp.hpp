#pragma once
#include <ecs/cmp/Component_t.hpp>
#include <game/utils/fvec2.hpp>

namespace AIP {

struct BulletCmp : BECS::Component_t {
    explicit BulletCmp(const BECS::entID entityID, const int64_t p_x, const int64_t p_y, BECS::entID eid, int64_t amount) 
    : Component_t(entityID), spawnPos(p_x, p_y), shooter(eid), damage(amount) { }

    fvec2<fint_t<int64_t>> spawnPos { { 0l }, { 0l } }; //posicion ini. 
    BECS::entID            shooter  { 0u };
    int64_t                damage   { 0  }; 
};

}