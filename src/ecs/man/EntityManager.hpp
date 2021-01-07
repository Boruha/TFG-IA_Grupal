#pragma once
#include <ecs/man/ComponentStorage.tpp>
#include <ecs/ent/Entity_t.hpp>

#include <game/utils/ufixed64_t.hpp>

namespace BECS {

//pasar templates al tpp
struct EntityManager {
      explicit EntityManager();

      EntityManager(const EntityManager& )            = delete;
      EntityManager(const EntityManager&&)            = delete;
      EntityManager& operator=(const EntityManager& ) = delete;
      EntityManager& operator=(const EntityManager&&) = delete;

      [[nodiscard]] Entity_t& createEntity_t() noexcept;

      template <typename T>
      void 
      addComponentToEntity(const T& new_cmp, const entID eid) noexcept {
            auto& ref_cmp = cmp_storage.createComponent(new_cmp);
            auto& ref_ent = getEntityByID(eid);

            ref_ent.addComponent(&ref_cmp);
      }
      
      template <typename CMP_t>
      std::vector<CMP_t>&
      getComponentVector() noexcept { 
            return cmp_storage.getCmpCollection<CMP_t>();
      }


      void deleteEntity(entID eid) noexcept; //necesita rework

      std::unordered_map<entID, Entity_t>&  getEntities()            noexcept { return ent_map; }
      Entity_t&                             getEntityByID(entID eid) noexcept { return ent_map.at(eid); }

private:
      std::unordered_map<entID, Entity_t> ent_map     { };
      ComponentStorage                    cmp_storage { };
};

} // namespace AIP