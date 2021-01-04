#pragma once

#include <utils/Alias.hpp>

#include <ent/Entity_t.hpp>

#include <vector>
#include <unordered_map>
#include <memory>

namespace AIP {

struct Entity_t;
struct RenderComponent;
struct MovementComponent;
struct AI_Component;
struct InputComponent;
struct CombatComponent;

struct Manager_t {
    virtual ~Manager_t() = default;

    virtual const std::unordered_map<entID, Entity_t>&  getEntities() const noexcept = 0;   
    virtual       std::unordered_map<entID, Entity_t>&  getEntities()       noexcept = 0;

    virtual const Entity_t&  getEntityByID(entID eid) const noexcept = 0;   
    virtual       Entity_t&  getEntityByID(entID eid)       noexcept = 0;

    virtual const std::vector<RenderComponent>&  getRenderCmps() const noexcept = 0;   
    virtual       std::vector<RenderComponent>&  getRenderCmps()       noexcept = 0;

    virtual const std::vector<MovementComponent>&  getMovementCmps() const noexcept = 0;   
    virtual       std::vector<MovementComponent>&  getMovementCmps()       noexcept = 0;

    virtual const std::vector<AI_Component>&  getAI_Cmps() const noexcept = 0;   
    virtual       std::vector<AI_Component>&  getAI_Cmps()       noexcept = 0;

    virtual const std::vector<InputComponent>&  getInputCmps() const noexcept = 0;   
    virtual       std::vector<InputComponent>&  getInputCmps()       noexcept = 0;

    virtual const std::vector<CombatComponent>&  getCombatCmps() const noexcept = 0;   
    virtual       std::vector<CombatComponent>&  getCombatCmps()       noexcept = 0;

    virtual const entID  getPlayerID() const noexcept = 0;   
    virtual       entID  getPlayerID()       noexcept = 0;

    virtual void deleteEntity(entID eid) noexcept = 0;
};

}
