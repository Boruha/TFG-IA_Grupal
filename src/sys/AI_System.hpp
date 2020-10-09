#pragma once
#include <sys/System_t.hpp>

namespace AIP {

struct Manager_t;
struct AI_Component;
struct MovementComponent;

struct AI_System : System_t {
    explicit  AI_System() = default;

    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept override;

private:
    //compound behaviour
    void patrol(std::unique_ptr<AI_Component>& ai_cmp, MovementComponent* mov_cmp) noexcept;
    
    //simple behaviour
    void seek(MovementComponent* mov_cmp, const float x, const float y) noexcept;
    bool arrive(float dist2obj) noexcept;
};


} //NS