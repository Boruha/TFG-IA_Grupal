#pragma once
#include <man/Manager_t.hpp>

#include <cstdint>

namespace AIP {  

struct EntityManager : Manager_t
{
    explicit EntityManager();
            ~EntityManager() override;
    
    void createEntity_t(const uint32_t coord_X, const uint32_t coord_Y);

    const std::vector<std::unique_ptr<Entity_t>>&  getEntities() const override { return ent_vector; }

private:
    std::vector<std::unique_ptr<Entity_t>> ent_vector { };
};

} // namespace AIP