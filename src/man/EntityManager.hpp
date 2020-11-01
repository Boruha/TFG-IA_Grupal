#pragma once
#include <man/Manager_t.hpp>
#include <man/ComponentStorage.hpp>

#include <ent/Flock_t.hpp>

#include <utils/Alias.hpp>
#include <utils/Color.hpp>

#include <cstdint>

namespace AIP {

struct EntityManager : Manager_t
{
      explicit EntityManager();
              ~EntityManager() override;

      [[nodiscard]] std::unique_ptr<Entity_t>& createEntity_t() noexcept;
      [[nodiscard]] std::unique_ptr<Flock_t>&  createFlock_t() noexcept;

      /*   GETTERS CONTEXT   */

      const std::unordered_map<entID, std::unique_ptr<Entity_t>>&  getEntities() const noexcept override { return ent_map; }
            std::unordered_map<entID, std::unique_ptr<Entity_t>>&  getEntities()       noexcept override { return ent_map; }
      
      const std::vector<std::unique_ptr<Flock_t>>&  getFlocks() const noexcept { return flock_vec; }   
            std::vector<std::unique_ptr<Flock_t>>&  getFlocks()       noexcept { return flock_vec; }


      const std::unique_ptr<Entity_t>&  getEntityByID(entID eid) const noexcept override { return ent_map.at(eid); }  
            std::unique_ptr<Entity_t>&  getEntityByID(entID eid)       noexcept override { return ent_map.at(eid); }

      const std::vector<std::unique_ptr<RenderComponent>>&  getRenderCmps() const noexcept override { return cmp_storage->getCmpCollection<RenderComponent>(); }
            std::vector<std::unique_ptr<RenderComponent>>&  getRenderCmps()       noexcept override { return cmp_storage->getCmpCollection<RenderComponent>(); }

      const std::vector<std::unique_ptr<MovementComponent>>&  getMovementCmps() const noexcept override { return cmp_storage->getCmpCollection<MovementComponent>(); }
            std::vector<std::unique_ptr<MovementComponent>>&  getMovementCmps()       noexcept override { return cmp_storage->getCmpCollection<MovementComponent>(); }

      const std::vector<std::unique_ptr<AI_Component>>&  getAI_Cmps() const noexcept { return cmp_storage->getCmpCollection<AI_Component>(); };   
            std::vector<std::unique_ptr<AI_Component>>&  getAI_Cmps()       noexcept { return cmp_storage->getCmpCollection<AI_Component>(); };

      const std::vector<std::unique_ptr<InputComponent>>&  getInputCmps() const noexcept override { return cmp_storage->getCmpCollection<InputComponent>(); }
            std::vector<std::unique_ptr<InputComponent>>&  getInputCmps()       noexcept override { return cmp_storage->getCmpCollection<InputComponent>(); }

private:
      std::unordered_map<entID, std::unique_ptr<Entity_t>> ent_map     { };
      std::vector<std::unique_ptr<Flock_t>>                flock_vec   { };
      std::unique_ptr<ComponentStorage>                    cmp_storage { std::make_unique<ComponentStorage>() };
};

} // namespace AIP