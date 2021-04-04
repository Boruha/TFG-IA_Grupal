#include <game/sys/DeathSystem.hpp>
#include <game/cmp/EventCmp_t.hpp>
#include <game/cmp/AI_Component.hpp>

#include <algorithm>
#include <iostream>
#include <vector>

namespace AIP {

template <typename Context_t>
GameConditions 
DeathSystem<Context_t>::update(Context_t& context) noexcept {
    auto& enemies_ids = context.getEnemyIDs();
    auto& allies_ids  = context.getAllyIDs();
    auto& eventCmp    = context.template getSCmpByType<EventCmp_t>();
    auto& death_vec   = eventCmp.death_msg;
    
    while( !death_vec.empty() ) {
        auto& msg = death_vec.front();
        
        switch (msg.type) {
            case EntType::Human:  {
                    dontHitMeImDead(eventCmp, msg.eid);
                    dontTargetMe(context.template getComponentVector<AI_Component>(), msg.eid);
                    context.deleteEntity(msg.eid);
                } break;
            case EntType::Bullet: { 
                    context.deleteBullet(msg.eid);
                } break;        
        }

        death_vec.pop();
        if( enemies_ids.size() == 0)
            return GameConditions::Victoria;

        if( allies_ids.size() == 0)
            return GameConditions::Derrota;
    }

    return GameConditions::Loop;
}

//We have to delete attks to deaths entities to avoid bad memory access in attk system.
inline void
dontHitMeImDead(EventCmp_t& eventCmp, const BECS::entID& eid) noexcept {
    auto& atk_msg = eventCmp.attack_msg;
    atk_msg.erase(  std::remove_if(atk_msg.begin(), atk_msg.end(),
                        [&](auto& msg) { return msg.eid_damaged == eid; }), 
                    atk_msg.end()
    );
}

inline void
dontTargetMe(std::vector<AI_Component>& ai_vec, const BECS::entID& eid) noexcept {
    std::for_each(ai_vec.begin(), ai_vec.end(),
        [&](auto& ai) { if( eid == ai.target_ent ) ai.target_ent = 0u; });
}

} // NS