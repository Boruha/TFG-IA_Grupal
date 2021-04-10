#pragma once
#include <game/cmp/RenderComponent.hpp>
#include <game/utils/fvec2.hpp>
#include <game/utils/vec2.tpp>

#include <engineGL/EngineManager.hpp>

#include <memory>

namespace AIP {

struct MovementComponent;
struct Collider2DCmp;

template <typename Context_t>
struct RenderSystem {
    explicit RenderSystem(const int64_t w, const int64_t h);

    bool update(Context_t& context) noexcept;
    
    bool debug_mode { false };
private:
    vec2<uint32_t> continuousToScreen(const fvec2<fint_t<int64_t>>& cont) noexcept;
    vec2<uint32_t> clipToDraw(fvec2<fint_t<int64_t>> point)               noexcept;
    
    void drawFacing(const MovementComponent& mov, const RenderComponent& render) noexcept;
    void drawInterface(Context_t& context) noexcept;
    void draw_debug(const MovementComponent& mov, const RenderComponent& render, const Collider2DCmp& coll2D ) noexcept;

    std::unique_ptr<eGL::EngineManager> engine { nullptr };
};

}
