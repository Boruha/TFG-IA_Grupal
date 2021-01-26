#pragma once
#include <ecs/man/EntityManager.tpp>

#include <vector>

namespace AIP {

struct UnitsManager {
      explicit UnitsManager() { }

      UnitsManager(const UnitsManager& )            = delete;
      UnitsManager(const UnitsManager&&)            = delete;
      UnitsManager& operator=(const UnitsManager& ) = delete;
      UnitsManager& operator=(const UnitsManager&&) = delete;

      void init()                        noexcept;
      void clear()                       noexcept;
      void deleteEntity(BECS::entID eid) noexcept;

      void createSoldier(const uint32_t size, const int64_t pos_x, const int64_t pos_y, const Color col, bool team) noexcept;
      void createPlayerPointer( const uint32_t size, const int64_t pos_x, const int64_t pos_y, const Color col)     noexcept;
    
      template <typename CMP_t> constexpr std::vector<CMP_t>& getComponentVector()                    noexcept;
      template <typename CMP_t> constexpr CMP_t&              getCmpByEntityID(const BECS::entID eid) noexcept;

      constexpr std::vector<BECS::entID>& getEnemyIDs() noexcept;
      constexpr std::vector<BECS::entID>& getAllyIDs() noexcept;

      BECS::Entity_t&    getEntityByID(BECS::entID eid)       noexcept;
      const BECS::entID  getPlayerID()                  const noexcept;  
            BECS::entID  getPlayerID()                        noexcept;

private:
      BECS::EntityManager ent_man   {    };
      BECS::entID         player_id { 0u };

      std::vector<BECS::entID> enemies_vec;
      std::vector<BECS::entID> allies_vec;
};

} // namespace AIP