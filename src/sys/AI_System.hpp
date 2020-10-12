#pragma once
#include <sys/System_t.hpp>
#include <utils/Vec2.hpp>

namespace AIP {

struct Manager_t;
struct Flock_t;
struct AI_Component;
struct MovementComponent;

struct AI_System : System_t {
    explicit  AI_System() = default;

    void init() noexcept override;
    bool update(const std::unique_ptr<Manager_t>& context, const float DeltaTime) noexcept override;

private:
    //old
    //void patrol(std::unique_ptr<AI_Component>& ai_cmp, MovementComponent* mov_cmp) noexcept;    //Gestiona el pathing
    //void seek(MovementComponent* mov_cmp, const float x, const float y) noexcept;  //actualiza la dir de las AIs. 

    void patrol(std::unique_ptr<Flock_t>& flock_ent) noexcept;
    void seek()   noexcept;

    bool arrive(float dist2obj) noexcept;                                          
};


} //NS