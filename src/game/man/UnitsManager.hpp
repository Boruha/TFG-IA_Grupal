/*
Copyright (C) <2020-2021> Borja Pozo Wals (Tw: @Chico_Riot | GitHub: Boruha)

This file is part of 'TFG: Gestión y manejo de comportamientos grupales 
de entidades en videojuegos'.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once
#include <ecs/man/EntityManager.tpp>
#include <game/utils/Patrol_t.hpp>

#include <vector>
#include <tuple>
#include <string>


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
      void deleteBullet(BECS::entID eid) noexcept;

      void loadLevel0();
      void loadLevel1();
      
      void deleteByIDFrom(std::vector<BECS::entID>& container, BECS::entID eid) noexcept;

      void createSoldier(      const uint32_t size, const int64_t pos_x, const int64_t pos_y, const Color col, bool team, Patrol_t& pat) noexcept;
      void createArcher(       const uint32_t size, const int64_t pos_x, const int64_t pos_y, const Color col, bool team, Patrol_t& pat) noexcept;
      void createTiggerBox(    const uint32_t sz_x, const uint32_t sz_y, const int64_t pos_x, const int64_t pos_y, GameConditions event) noexcept;
      void createMessage(      const uint32_t sz_x, const uint32_t sz_y, const int64_t pos_x, const int64_t pos_y, std::string mensaje)  noexcept;
      void createPlayerPointer(const uint32_t size, const int64_t pos_x, const int64_t pos_y, const Color col    ) noexcept;
      void createCamera(       const uint32_t sz_x, const uint32_t sz_y, const int64_t pos_x, const int64_t pos_y) noexcept;
      
      void createBullet(fvec2<fint_t<int64_t>> nDir, const int64_t pos_x, const int64_t pos_y, bool team, BECS::entID eid, int64_t amount) noexcept;


      template <typename CMP_t>  constexpr std::vector<CMP_t>& getComponentVector()                    noexcept;
      template <typename CMP_t>  constexpr CMP_t&              getCmpByEntityID(const BECS::entID eid) noexcept;
      template <typename SCMP_t> constexpr SCMP_t&             getSCmpByType()                         noexcept;

      constexpr std::vector<BECS::entID>& getEnemyIDs()    noexcept;
      constexpr std::vector<BECS::entID>& getAllyIDs()     noexcept;
      constexpr std::vector<BECS::entID>& getEnemBullets() noexcept;
      constexpr std::vector<BECS::entID>& getAllyBullets() noexcept;

      BECS::Entity_t&    getEntityByID(BECS::entID eid)       noexcept;
      const BECS::entID  getPlayerID()                  const noexcept;  
            BECS::entID  getPlayerID()                        noexcept;
            BECS::entID  getCameraID()                        noexcept;

private:
      BECS::EntityManager ent_man   {    };
      BECS::entID         player_id { 0u };
      BECS::entID         camera_id { 0u };

      std::vector<BECS::entID> enemies_vec;
      std::vector<BECS::entID> allies_vec;
      std::vector<BECS::entID> ally_bullets;
      std::vector<BECS::entID> enem_bullets;
      std::vector<Patrol_t>    patrols;

      std::tuple<InterfaceControl, EventCmp_t, BlackBoardCmp> singletonCmps { };
};

} // namespace AIP