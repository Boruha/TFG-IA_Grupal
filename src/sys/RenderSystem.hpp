#pragma once
#include <sys/System_t.hpp>

#include <cstdint>

namespace AIP {

struct Manager_t;

struct RenderSystem : System_t {
    explicit RenderSystem(const uint32_t w, const uint32_t h);
            ~RenderSystem() override;

    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept override;
    
private:
    const uint32_t window_w { 0 }, window_h { 0 }, framebuffer_size { 0 };
    std::unique_ptr<uint32_t[]> framebuffer { nullptr };
};

}
