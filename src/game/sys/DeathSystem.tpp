#include <game/sys/DeathSystem.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

template <typename Context_t>
GameConditions 
DeathSystem<Context_t>::update(Context_t& context) noexcept {
    auto& enemies_ids = context.template getEnemyIDs();
    auto& allies_ids  = context.template getAllyIDs();

    while( !death_msg.empty() ) {
        auto& msg = death_msg.front();
        
        switch (msg.type) {
            case EntType::Human:  context.deleteEntity(msg.eid);
                break;
            case EntType::Bullet: context.deleteBullet(msg.eid);
                break;        
        }

        death_msg.pop();
        if( enemies_ids.size() == 0)
            return GameConditions::Victoria;

        if( allies_ids.size() == 0)
            return GameConditions::Derrota;
    }
    
    return GameConditions::Loop;
}

} // NS