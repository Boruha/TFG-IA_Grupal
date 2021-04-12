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
      const std::size_t                   MAX_ENTITIES { 10u };
};

} // namespace AIP