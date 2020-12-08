#pragma once
#include <man/Manager_t.hpp>
#include <man/ComponentStorage.hpp>

namespace AIP {

//crear usings para hacer más legible el documento
struct EntityManager : Manager_t {
      explicit EntityManager();

      EntityManager(const EntityManager& )            = delete;
      EntityManager(const EntityManager&&)            = delete;
      EntityManager& operator=(const EntityManager& ) = delete;
      EntityManager& operator=(const EntityManager&&) = delete;

      void init() noexcept;

      [[nodiscard]] std::unique_ptr<Entity_t>& createEntity_t() noexcept;
      void createSoldier(const ufixed64_t& size, const fixed64_t& pos_x, const fixed64_t& pos_y, const Color col) noexcept;
      

      /*   GETTERS CONTEXT   */
      const std::unordered_map<entID, std::unique_ptr<Entity_t>>&  getEntities() const noexcept override { return ent_map; }
            std::unordered_map<entID, std::unique_ptr<Entity_t>>&  getEntities()       noexcept override { return ent_map; }

      const std::unique_ptr<Entity_t>&  getEntityByID(entID eid) const noexcept override { return ent_map.at(eid); }  
            std::unique_ptr<Entity_t>&  getEntityByID(entID eid)       noexcept override { return ent_map.at(eid); }

      const std::vector<std::unique_ptr<RenderComponent>>&  getRenderCmps() const noexcept override { return cmp_storage->getCmpCollection<RenderComponent>(); }
            std::vector<std::unique_ptr<RenderComponent>>&  getRenderCmps()       noexcept override { return cmp_storage->getCmpCollection<RenderComponent>(); }

      const std::vector<std::unique_ptr<MovementComponent>>&  getMovementCmps() const noexcept override { return cmp_storage->getCmpCollection<MovementComponent>(); }
            std::vector<std::unique_ptr<MovementComponent>>&  getMovementCmps()       noexcept override { return cmp_storage->getCmpCollection<MovementComponent>(); }

      const std::vector<std::unique_ptr<AI_Component>>&  getAI_Cmps() const noexcept override { return cmp_storage->getCmpCollection<AI_Component>(); };   
            std::vector<std::unique_ptr<AI_Component>>&  getAI_Cmps()       noexcept override { return cmp_storage->getCmpCollection<AI_Component>(); };

      const std::vector<std::unique_ptr<InputComponent>>&  getInputCmps() const noexcept override { return cmp_storage->getCmpCollection<InputComponent>(); }
            std::vector<std::unique_ptr<InputComponent>>&  getInputCmps()       noexcept override { return cmp_storage->getCmpCollection<InputComponent>(); }

      const entID  getPlayerID() const noexcept override { return player_id; };   
            entID  getPlayerID()       noexcept override { return player_id; };

private:
      std::unordered_map<entID, std::unique_ptr<Entity_t>> ent_map     { };
      std::unique_ptr<ComponentStorage>                    cmp_storage { std::make_unique<ComponentStorage>() };
      entID player_id { 0u };
};

} // namespace AIP