#pragma once
#include <vector>
#include <unordered_map>
#include <memory>

#include <utils/Alias.hpp>

namespace AIP {

struct Entity_t;
struct RenderComponent;
struct MovementComponent;

struct Manager_t {
    virtual ~Manager_t() = default;

    virtual const std::unordered_map<entID, std::unique_ptr<Entity_t>>&  getEntities() const = 0;   
    virtual       std::unordered_map<entID, std::unique_ptr<Entity_t>>&  getEntities()       = 0;

    virtual const std::unique_ptr<Entity_t>&  getEntityByID(entID eid) const = 0;   
    virtual       std::unique_ptr<Entity_t>&  getEntityByID(entID eid)       = 0;

    virtual const std::vector<std::unique_ptr<RenderComponent>>&  getRenderCmps() const = 0;   
    virtual       std::vector<std::unique_ptr<RenderComponent>>&  getRenderCmps()       = 0;

    virtual const std::vector<std::unique_ptr<MovementComponent>>&  getMovementCmps() const = 0;   
    virtual       std::vector<std::unique_ptr<MovementComponent>>&  getMovementCmps()       = 0;

};

}
