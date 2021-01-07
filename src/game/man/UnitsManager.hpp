#pragma once
#include <ecs/man/EntityManager.hpp>

namespace AIP {

struct UnitsManager {
      explicit UnitsManager() { }

      UnitsManager(const UnitsManager& )            = delete;
      UnitsManager(const UnitsManager&&)            = delete;
      UnitsManager& operator=(const UnitsManager& ) = delete;
      UnitsManager& operator=(const UnitsManager&&) = delete;

      void init() noexcept;

      void createSoldier(const ufixed64_t& size, const fixed64_t& pos_x, const fixed64_t& pos_y, const Color col) noexcept;
      void createPlayer(const ufixed64_t& size, const fixed64_t& pos_x, const fixed64_t& pos_y, const Color col) noexcept;
    
      template <typename CMP_t>
      std::vector<CMP_t>&
      getComponentVector() noexcept {
            return ent_man.getComponentVector<CMP_t>();
      }

      template<typename CMP_t> constexpr 
      CMP_t& 
      getCmpByEntityID(const BECS::entID eid) noexcept {
            return ent_man.getCmpByEntityID<CMP_t>(eid);
      }

      void deleteEntity(BECS::entID eid) noexcept { return ent_man.deleteEntity(eid); }

      BECS::Entity_t& getEntityByID(BECS::entID eid) noexcept { return ent_man.getEntityByID(eid); }

      const BECS::entID  getPlayerID() const noexcept { return player_id; };   
            BECS::entID  getPlayerID()       noexcept { return player_id; };

private:
      BECS::EntityManager ent_man   {    };
      BECS::entID         player_id { 0u };
};

} // namespace AIP