#include <game/sys/BulletLifeSystem.hpp>

#include <iostream>
#include <algorithm>

namespace AIP {

template <typename Context_t>
void
BulletLifeSystem<Context_t>::update(Context_t& context) noexcept {
    //checking life diff
    auto lifeCheck = [&](BECS::entID& bullet) {
        auto& mov  = context.template getCmpByEntityID<MovementComponent>(bullet);
        
        constexpr fint_t<int64_t> dist { 100l };
        auto  diff { mov.coords - mov.spawnPos };

        if( dist < diff.length() )
            death_msg.emplace(bullet, EntType::Bullet);
    };

    auto& eneBullets  = context.template getEnemBullets();
    auto& allyBullets = context.template getAllyBullets();

    std::for_each( begin(eneBullets) , end(eneBullets) , lifeCheck );
    std::for_each( begin(allyBullets), end(allyBullets), lifeCheck );

    //new bullets spawning
    while ( !bullet_msg.empty() ) {
        auto& msg = bullet_msg.front();
        context.template createBullet(msg.nDir, msg.pos_x, msg.pos_y, msg.team);
        bullet_msg.pop();
    }

}

} //NS