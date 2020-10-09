#pragma once
#include <sys/System_t.hpp>

#include <memory>

namespace AIP {

struct Manager_t;

struct MovementSystem : System_t {
    explicit MovementSystem() = default;
    
    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept override;
};

} //NS
