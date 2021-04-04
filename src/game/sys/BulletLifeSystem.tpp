#include <game/sys/BulletLifeSystem.hpp>

#include <game/cmp/BulletCmp.hpp>
#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/EventCmp_t.hpp>

#include <iostream>
#include <algorithm>

namespace AIP {

template <typename Context_t>
void
BulletLifeSystem<Context_t>::update(Context_t& context) noexcept {
    constexpr fint_t<int64_t> dist { 300l };

    //checking life diff
    auto lifeCheck = [&](BECS::entID& bullet) {
        auto& mov  = context.template getCmpByEntityID<MovementComponent>(bullet);
        auto& bull = context.template getCmpByEntityID<BulletCmp>(bullet);        

        auto  diff { mov.coords - bull.spawnPos };

        if( dist < diff.length() ) {
            auto& eventCmp = context.template getSCmpByType<EventCmp_t>();
            eventCmp.death_msg.emplace(bullet, EntType::Bullet);
        }
    };

    auto& eneBullets  = context.getEnemBullets();
    auto& allyBullets = context.getAllyBullets();

    std::for_each( begin(eneBullets) , end(eneBullets) , lifeCheck );
    std::for_each( begin(allyBullets), end(allyBullets), lifeCheck );

    spawnBullets(context);
}

template <typename Context_t>
void 
BulletLifeSystem<Context_t>::spawnBullets(Context_t& context) noexcept {
    auto& eventCmp   = context.template getSCmpByType<EventCmp_t>();
    auto& bullet_vec = eventCmp.bullet_msg;
    
    while ( !bullet_vec.empty() ) {
        auto& msg = bullet_vec.front();
        context.createBullet(msg.nDir, msg.pos_x, msg.pos_y, msg.team, msg.shooter, msg.amount);
        bullet_vec.pop();
    }
}


} //NS