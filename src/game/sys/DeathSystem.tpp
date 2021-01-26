#include <game/sys/DeathSystem.hpp>

#include <algorithm>
#include <iostream>

namespace AIP {

template <typename Context_t>
bool 
DeathSystem<Context_t>::update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept {
    auto& enemies_ids = context.template getEnemyIDs();
    auto& allies_ids  = context.template getAllyIDs();

    while( !death_msg.empty() ) {
        context.deleteEntity(death_msg.front().eid);
        death_msg.pop();
        std::cout << "Enemies: " << enemies_ids.size() << "\n";
        std::cout << "Allies : " << allies_ids.size() << "\n";
    }
    
    return true;
}

} // NS