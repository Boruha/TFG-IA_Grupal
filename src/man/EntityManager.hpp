#pragma once
#include <man/Manager_t.hpp>

#include <utils/Color.hpp>

#include <cstdint>

namespace AIP {  

struct EntityManager : Manager_t
{
    explicit EntityManager();
            ~EntityManager() override;
    
    //void createEntity_t(const uint32_t coord_X , const uint32_t coord_Y);
    [[nodiscard]] std::unique_ptr<Entity_t>& createEntity_t();

    [[nodiscard]] std::unique_ptr<RenderComponent>&   createRend_Cmp(const uint32_t entityID, const uint32_t size_W, const uint32_t size_H, const Color col);
    [[nodiscard]] std::unique_ptr<MovementComponent>& createMove_Cmp(const uint32_t entityID, const uint32_t coord_X, const uint32_t coord_Y);

    const std::unordered_map<entID, std::unique_ptr<Entity_t>>&  getEntities() const override { return ent_map; }
          std::unordered_map<entID, std::unique_ptr<Entity_t>>&  getEntities()       override { return ent_map; }

    const std::unique_ptr<Entity_t>&  getEntityByID(entID eid) const override { return ent_map.at(eid); }  
          std::unique_ptr<Entity_t>&  getEntityByID(entID eid)       override { return ent_map.at(eid); }

    const std::vector<std::unique_ptr<RenderComponent>>&  getRenderCmps() const override { return render_cmps; }
          std::vector<std::unique_ptr<RenderComponent>>&  getRenderCmps()       override { return render_cmps; }

    const std::vector<std::unique_ptr<MovementComponent>>&  getMovementCmps() const override { return movement_cmps; }
          std::vector<std::unique_ptr<MovementComponent>>&  getMovementCmps()       override { return movement_cmps; }

private:
    std::unordered_map<entID, std::unique_ptr<Entity_t>> ent_map { };
    std::vector<std::unique_ptr<RenderComponent>> render_cmps { };
    std::vector<std::unique_ptr<MovementComponent>> movement_cmps { };
};

} // namespace AIP