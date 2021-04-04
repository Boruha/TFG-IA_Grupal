#pragma once
#include <game/utils/fvec2.hpp>

#include <ecs/utils/Alias.hpp>

namespace AIP {

enum class EntType {
    Human  = 0,
    Bullet = 1
};

struct BulletSpawn {
    constexpr explicit BulletSpawn(BECS::entID eid, const fvec2<fint_t<int64_t>> dir, const int64_t p_x, const int64_t p_y, bool team_, int64_t size)
                        : shooter(eid), nDir(dir), pos_x(p_x), pos_y(p_y), team(team_), amount(size) { }
                        
    BECS::entID shooter { 0u };               
    fvec2<fint_t<int64_t>> nDir { 0l, 0l };
    int64_t pos_x  { 0l };
    int64_t pos_y  { 0l };
    bool    team   { false };
    int64_t amount { 0  };
};

struct AttackMessage {
    constexpr explicit AttackMessage(BECS::entID eid1, BECS::entID eid2, int64_t size) 
        : eid_deal(eid1), eid_damaged(eid2), amount(size) { }

    BECS::entID eid_deal    { 0u };
    BECS::entID eid_damaged { 0u };
    int64_t     amount      { 0  };
};

struct DeathMessage {
    constexpr explicit DeathMessage(BECS::entID id, EntType entType)
        : eid(id), type(entType) { }

    BECS::entID eid  { 0u };
    EntType     type { EntType::Bullet };
};


} // NS
