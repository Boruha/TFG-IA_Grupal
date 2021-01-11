#pragma once
#include <ecs/man/EntityManager.tpp>

#include <game/utils/fvec2.tpp>

namespace AIP {

struct UnitsManager {
      explicit UnitsManager() { }

      UnitsManager(const UnitsManager& )            = delete;
      UnitsManager(const UnitsManager&&)            = delete;
      UnitsManager& operator=(const UnitsManager& ) = delete;
      UnitsManager& operator=(const UnitsManager&&) = delete;

      void init()                        noexcept;
      void deleteEntity(BECS::entID eid) noexcept;

      void createSoldier(const fint_t<uint64_t>& size, const fint_t<int64_t>& pos_x, const fint_t<int64_t>& pos_y, const Color col) noexcept;
      void createPlayer( const fint_t<uint64_t>& size, const fint_t<int64_t>& pos_x, const fint_t<int64_t>& pos_y, const Color col) noexcept;
    
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