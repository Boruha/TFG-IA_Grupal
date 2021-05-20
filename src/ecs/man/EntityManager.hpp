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
#include <ecs/man/ComponentStorage.tpp>
#include <ecs/ent/Entity_t.hpp>

namespace BECS {

struct EntityManager {
      explicit EntityManager();

      EntityManager(const EntityManager& )            = delete;
      EntityManager(const EntityManager&&)            = delete;
      EntityManager& operator=(const EntityManager& ) = delete;
      EntityManager& operator=(const EntityManager&&) = delete;

      void clear() noexcept;

      [[nodiscard]] const entID     createEntity_t()         noexcept;
                          void      deleteEntity(entID eid)  noexcept;
                          Entity_t& getEntityByID(entID eid) noexcept;

      template <typename CMP_t>           CMP_t&              addComponentToEntity(const entID eid, const CMP_t&& new_cmp) noexcept;
      template <typename CMP_t> constexpr std::vector<CMP_t>& getComponentVector()                                        noexcept;
      template <typename CMP_t> constexpr CMP_t&              getCmpByEntityID(const entID eid)                           noexcept;

private:
      std::unordered_map<entID, Entity_t> ent_map      {     };
      ComponentStorage                    cmp_storage  {     };
      const std::size_t                   MAX_ENTITIES { 50u };
};

} // namespace AIP