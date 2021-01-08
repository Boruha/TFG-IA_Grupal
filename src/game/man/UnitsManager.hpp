#pragma once
#include <ecs/man/EntityManager.tpp>

namespace AIP {

struct UnitsManager {
      explicit UnitsManager() { }

      UnitsManager(const UnitsManager& )            = delete;
      UnitsManager(const UnitsManager&&)            = delete;
      UnitsManager& operator=(const UnitsManager& ) = delete;
      UnitsManager& operator=(const UnitsManager&&) = delete;

      void init()                        noexcept;
      void deleteEntity(BECS::entID eid) noexcept;

      void createSoldier(const ufixed64_t& size, const fixed64_t& pos_x, const fixed64_t& pos_y, const Color col) noexcept;
      void createPlayer( const ufixed64_t& size, const fixed64_t& pos_x, const fixed64_t& pos_y, const Color col) noexcept;
    
      template <typename CMP_t> constexpr std::vector<CMP_t>& getComponentVector()                    noexcept;
      template <typename CMP_t> constexpr CMP_t&              getCmpByEntityID(const BECS::entID eid) noexcept;


      BECS::Entity_t&    getEntityByID(BECS::entID eid)       noexcept;
      const BECS::entID  getPlayerID()                  const noexcept;  
            BECS::entID  getPlayerID()                        noexcept;

private:
      BECS::EntityManager ent_man   {    };
      BECS::entID         player_id { 0u };
};

} // namespace AIP