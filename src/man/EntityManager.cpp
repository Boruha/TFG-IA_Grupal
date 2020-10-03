#include <man/EntityManager.hpp>

#include <ent/Entity_t.hpp>

#include <cmp/MovementComponent.hpp>
#include <cmp/RenderComponent.hpp>

namespace AIP {

constexpr const uint32_t MAX_ENTITIES { 10 };

EntityManager::EntityManager() {
    render_cmps.reserve(MAX_ENTITIES);
    movement_cmps.reserve(MAX_ENTITIES);

    auto& ent1  = createEntity_t();
    auto& mov_1 = createMove_Cmp(ent1->getID(), 30U, 30U);
    auto& ren_1 = createRend_Cmp(ent1->getID(), 10U, 10U, Color::Black);

    ent1->addComponent(mov_1.get());
    ent1->addComponent(ren_1.get());

    auto& ent2  = createEntity_t();
    auto& mov_2 = createMove_Cmp(ent2->getID(), 100U, 100U);
    auto& ren_2 = createRend_Cmp(ent2->getID(), 10U, 10U, Color::Blue);

    ent2->addComponent(mov_2.get());
    ent2->addComponent(ren_2.get());
}

EntityManager::~EntityManager() {
    ent_map.clear();
    render_cmps.clear();
    movement_cmps.clear();
}

std::unique_ptr<Entity_t>&
EntityManager::createEntity_t() {
    auto new_ent { std::make_unique<Entity_t>() };
    return ent_map[new_ent->getID()] = std::move(new_ent);
}

std::unique_ptr<RenderComponent>& 
EntityManager::createRend_Cmp(const uint32_t entityID, const uint32_t size_W, const uint32_t size_H, const Color col) {
    return render_cmps.emplace_back( std::make_unique<RenderComponent>(entityID, size_W, size_H, col) );
}

std::unique_ptr<MovementComponent>& 
EntityManager::createMove_Cmp(const uint32_t entityID, const uint32_t coord_X, const uint32_t coord_Y) {
    return movement_cmps.emplace_back( std::make_unique<MovementComponent>(entityID, coord_X, coord_Y) );
}



} // namespace AIP
