#pragma once
#include <man/ComponentStorage.tpp>

#include <ent/Entity_t.hpp>

namespace AIP {

//crear usings para hacer más legible el documento
struct EntityManager {
      explicit EntityManager();

      EntityManager(const EntityManager& )            = delete;
      EntityManager(const EntityManager&&)            = delete;
      EntityManager& operator=(const EntityManager& ) = delete;
      EntityManager& operator=(const EntityManager&&) = delete;

      void init() noexcept;

      [[nodiscard]] Entity_t& createEntity_t() noexcept;
      void deleteEntity(entID eid) noexcept;

      void createSoldier(const ufixed64_t& size, const fixed64_t& pos_x, const fixed64_t& pos_y, const Color col) noexcept;

      /*   GETTERS CONTEXT   */
      /*const std::unordered_map<entID, Entity_t>&  getEntities() const noexcept override { return ent_map; }
            std::unordered_map<entID, Entity_t>&  getEntities()       noexcept override { return ent_map; }

      const Entity_t&  getEntityByID(entID eid) const noexcept override { return ent_map.at(eid); }  
            Entity_t&  getEntityByID(entID eid)       noexcept override { return ent_map.at(eid); }

      const std::vector<RenderComponent>&  getRenderCmps() const noexcept override { return cmp_storage.getCmpCollection<RenderComponent>(); }
            std::vector<RenderComponent>&  getRenderCmps()       noexcept override { return cmp_storage.getCmpCollection<RenderComponent>(); }

      const std::vector<MovementComponent>&  getMovementCmps() const noexcept override { return cmp_storage.getCmpCollection<MovementComponent>(); }
            std::vector<MovementComponent>&  getMovementCmps()       noexcept override { return cmp_storage.getCmpCollection<MovementComponent>(); }

      const std::vector<AI_Component>&  getAI_Cmps() const noexcept override { return cmp_storage.getCmpCollection<AI_Component>(); };   
            std::vector<AI_Component>&  getAI_Cmps()       noexcept override { return cmp_storage.getCmpCollection<AI_Component>(); };

      const std::vector<InputComponent>&  getInputCmps() const noexcept override { return cmp_storage.getCmpCollection<InputComponent>(); }
            std::vector<InputComponent>&  getInputCmps()       noexcept override { return cmp_storage.getCmpCollection<InputComponent>(); }

      const std::vector<CombatComponent>&  getCombatCmps() const noexcept override { return cmp_storage.getCmpCollection<CombatComponent>(); }
            std::vector<CombatComponent>&  getCombatCmps()       noexcept override { return cmp_storage.getCmpCollection<CombatComponent>(); }
      */

      std::unordered_map<entID, Entity_t>&  getEntities()            noexcept { return ent_map; }
      Entity_t&                             getEntityByID(entID eid) noexcept { return ent_map.at(eid); }


      template <typename CMP_t>
      std::vector<CMP_t>&  
      getComponentVector() noexcept { 
            return cmp_storage.getCmpCollection<CMP_t>(); 
      }


      const entID  getPlayerID() const noexcept { return player_id; };   
            entID  getPlayerID()       noexcept { return player_id; };

private:
      std::unordered_map<entID, Entity_t> ent_map     { };
      ComponentStorage                    cmp_storage { };
      entID                               player_id   { 0u };
};

} // namespace AIP