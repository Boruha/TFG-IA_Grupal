#pragma once
#include <man/Manager_t.hpp>
#include <man/ComponentStorage.hpp>

#include <utils/Alias.hpp>
#include <utils/Color.hpp>

#include <cstdint>

namespace AIP {

struct EntityManager : Manager_t
{
    explicit EntityManager();
            ~EntityManager() override;
    
    [[nodiscard]] std::unique_ptr<Entity_t>& createEntity_t();

    /*   GETTERS CONTEXT   */

    const std::unordered_map<entID, std::unique_ptr<Entity_t>>&  getEntities() const override { return ent_map; }
          std::unordered_map<entID, std::unique_ptr<Entity_t>>&  getEntities()       override { return ent_map; }

    const std::unique_ptr<Entity_t>&  getEntityByID(entID eid) const override { return ent_map.at(eid); }  
          std::unique_ptr<Entity_t>&  getEntityByID(entID eid)       override { return ent_map.at(eid); }

    const std::vector<std::unique_ptr<RenderComponent>>&  getRenderCmps() const override { return cmp_storage->getCmpCollection<RenderComponent>(); }
          std::vector<std::unique_ptr<RenderComponent>>&  getRenderCmps()       override { return cmp_storage->getCmpCollection<RenderComponent>(); }

    const std::vector<std::unique_ptr<MovementComponent>>&  getMovementCmps() const override { return cmp_storage->getCmpCollection<MovementComponent>(); }
          std::vector<std::unique_ptr<MovementComponent>>&  getMovementCmps()       override { return cmp_storage->getCmpCollection<MovementComponent>(); }

private:
    std::unordered_map<entID, std::unique_ptr<Entity_t>> ent_map { };

    std::unique_ptr<ComponentStorage> cmp_storage { std::make_unique<ComponentStorage>() };
};

} // namespace AIP