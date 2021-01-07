#include <game/sys/CollisionSystem.hpp>
#include <game/cmp/MovementComponent.hpp>
#include <game/cmp/RenderComponent.hpp>
#include <game/utils/ScreenData.hpp>

#include <ecs/ent/Entity_t.hpp>

#include <algorithm>

namespace AIP {

template <typename Context_t>
bool
CollisionSystem<Context_t>::update(Context_t& context, const fixed64_t DeltaTime) noexcept {
    auto& mov_cmp_vec = context.template getComponentVector<MovementComponent>();

    std::for_each(begin(mov_cmp_vec), end(mov_cmp_vec), 
        [&](MovementComponent& mov_cmp) {
                auto& ren_cmp   = context.template getCmpByEntityID<RenderComponent>( mov_cmp.getEntityID() );

                      auto& coord  = mov_cmp.coords;
                const auto size_W  = static_cast<fixed64_t>(ren_cmp.sprite.x);
                const auto size_H  = static_cast<fixed64_t>(ren_cmp.sprite.y);

                //eje X
                if( coord.x + size_W > HALF_WINDOW_W )
                        coord.x = (HALF_WINDOW_W * -1) + size_W;

                if( coord.x - size_W < (HALF_WINDOW_W * -1) )
                        coord.x = HALF_WINDOW_W - size_W;

                //eje Y
                if( coord.y + size_H > HALF_WINDOW_H )
                        coord.y = (HALF_WINDOW_H * -1) + size_H;

                if( coord.y - size_H < (HALF_WINDOW_H * -1) )
                        coord.y = HALF_WINDOW_H - size_H;
    });

    return true;
}

} //NS