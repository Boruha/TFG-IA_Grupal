#pragma once
#include <sys/System_t.hpp>

#include <utils/Vec2.hpp>

#include <cmp/RenderComponent.hpp>

namespace AIP {

struct Manager_t;
struct MovementComponent;

struct RenderSystem : System_t {
    explicit RenderSystem(const uint32_t w, const uint32_t h);
            ~RenderSystem() override;

    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const fixed64_t DeltaTime) noexcept override;
    
private:
    vec2<uint32_t> continuous_to_screen(const fixed_vec2& cont) noexcept;
    void bresenham_line(MovementComponent* mov_cmp, const std::unique_ptr<RenderComponent>& render_cmp) noexcept;
    
    void draw_line_X(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, int32_t dY, const int32_t dX, const Color& color) noexcept;
    void draw_line_Y(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, int32_t dX, const int32_t dY, const Color& color) noexcept;
    void draw_line_H(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, const Color& color) noexcept;    
    void draw_line_V(const vec2<uint32_t>& p_ini, const vec2<uint32_t>& p_end, const Color& color) noexcept;

    const uint32_t window_w { 0 }, window_h { 0 }, half_window_w { 0 }, half_window_h { 0 }, framebuffer_size { 0 };
    const fixed64_t half_window_w64 { 0l }, half_window_h64 { 0l };
    std::unique_ptr<uint32_t[]> framebuffer { nullptr };
};

}
