#pragma once
#include <sys/System_t.hpp>

#include <utils/Vec2.hpp>

#include <vector>

namespace AIP {

struct Manager_t;
struct Flock_t;
struct Entity_t;
struct AI_Component;
struct MovementComponent;

struct AI_System : System_t {
    explicit  AI_System() = default;

    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept override;

private:
    /*Patrol behaviours*/
    void patrol(std::unique_ptr<Flock_t>& flock_ent)               noexcept;
    void patrol_target_update(std::unique_ptr<Flock_t>& flock_ent) noexcept;

    /*Flock behaviours*/
    void cohesion(MovementComponent* mov_cmp, const Vec2<float>& flock_mc) noexcept;
    void separation(std::vector<Entity_t*>& squadron) noexcept;

    /*Generic behaviours*/
    void arrive(MovementComponent* mov_cmp, const Vec2<float>& target) noexcept;                                          
};


} //NS