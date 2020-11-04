#pragma once
#include <vector>
#include <unordered_map>
#include <memory>

#include <utils/Alias.hpp>

namespace AIP {

struct Entity_t;
struct Flock_t;
struct RenderComponent;
struct MovementComponent;
struct AI_Component;
struct InputComponent;


struct Manager_t {
    virtual ~Manager_t() = default;

    virtual const std::unordered_map<entID, std::unique_ptr<Entity_t>>&  getEntities() const noexcept = 0;   
    virtual       std::unordered_map<entID, std::unique_ptr<Entity_t>>&  getEntities()       noexcept = 0;

    virtual const std::vector<std::unique_ptr<Flock_t>>&  getFlocks() const noexcept = 0;   
    virtual       std::vector<std::unique_ptr<Flock_t>>&  getFlocks()       noexcept = 0;

    virtual const std::unique_ptr<Entity_t>&  getEntityByID(entID eid) const noexcept = 0;   
    virtual       std::unique_ptr<Entity_t>&  getEntityByID(entID eid)       noexcept = 0;

    virtual const std::vector<std::unique_ptr<RenderComponent>>&  getRenderCmps() const noexcept = 0;   
    virtual       std::vector<std::unique_ptr<RenderComponent>>&  getRenderCmps()       noexcept = 0;

    virtual const std::vector<std::unique_ptr<MovementComponent>>&  getMovementCmps() const noexcept = 0;   
    virtual       std::vector<std::unique_ptr<MovementComponent>>&  getMovementCmps()       noexcept = 0;

    virtual const std::vector<std::unique_ptr<AI_Component>>&  getAI_Cmps() const noexcept = 0;   
    virtual       std::vector<std::unique_ptr<AI_Component>>&  getAI_Cmps()       noexcept = 0;

    virtual const std::vector<std::unique_ptr<InputComponent>>&  getInputCmps() const noexcept = 0;   
    virtual       std::vector<std::unique_ptr<InputComponent>>&  getInputCmps()       noexcept = 0;

    virtual const entID  getPlayerID() const noexcept = 0;   
    virtual       entID  getPlayerID()       noexcept = 0;

};

}
