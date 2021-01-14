#pragma once
#include <game/cmp/RenderComponent.hpp>
#include <game/utils/vec2.tpp>

namespace AIP {

struct MovementComponent;

template <typename Context_t>
struct RenderSystem {
    explicit RenderSystem(const uint32_t w, const uint32_t h);
            ~RenderSystem();

    void init() noexcept;
    bool update(Context_t& context, const fint_t<int64_t> DeltaTime) noexcept;
    
private:
    vec2<uint32_t> continuous_to_screen(const fvec2<fint_t<int64_t>>& cont) noexcept;
    void draw_debug(const MovementComponent& mov_cmp, const RenderComponent& render_cmp) noexcept;
    void bresenham_line(const vec2<uint32_t>& screen_p_ini, const vec2<uint32_t>& screen_p_fin, int32_t dY, int32_t dX, const Color& color) noexcept;
    
    void draw_line_X(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, int32_t dY, const int32_t dX, const Color& color) noexcept;
    void draw_line_Y(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, int32_t dX, const int32_t dY, const Color& color) noexcept;
    void draw_line_H(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, const Color& color) noexcept;    
    void draw_line_V(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, const Color& color) noexcept;

    const uint32_t window_w { 0 }, window_h { 0 }, half_window_w { 0 }, half_window_h { 0 }, framebuffer_size { 0 };
    const fint_t<int64_t> half_window_w64 { 0l }, half_window_h64 { 0l };
    std::unique_ptr<uint32_t[]> framebuffer { nullptr };
    bool debug_mode { false };
};

}
