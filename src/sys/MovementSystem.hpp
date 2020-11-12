#pragma once
#include <sys/System_t.hpp>

#include <utils/AI_Constants.hpp>

#include <memory>

namespace AIP {

struct Manager_t;
struct MovementComponent;

struct MovementSystem : System_t {
    explicit MovementSystem() = default;
    
    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const fixed64_t DeltaTime) noexcept override;
};

} //NS
