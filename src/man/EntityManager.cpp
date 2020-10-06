#include <man/EntityManager.hpp>

#include <ent/Entity_t.hpp>

#include <cmp/MovementComponent.hpp>
#include <cmp/RenderComponent.hpp>

namespace AIP {

constexpr const uint32_t MAX_ENTITIES { 10 };

EntityManager::EntityManager() {
    
    auto& ent1  = createEntity_t();
    auto& mov_1 = cmp_storage->createComponent( MovementComponent(ent1->getID(), 30U, 30U) );
    auto& ren_1 = cmp_storage->createComponent( RenderComponent(ent1->getID(), 10U, 10U, Color::White) );

    ent1->addComponent(mov_1.get());
    ent1->addComponent(ren_1.get());

    auto& ent2  = createEntity_t();
    auto& mov_2 = cmp_storage->createComponent( MovementComponent(ent2->getID(), 100U, 100U) );
    auto& ren_2 = cmp_storage->createComponent( RenderComponent(ent2->getID(), 10U, 10U, Color::Green) );

    ent2->addComponent(mov_2.get());
    ent2->addComponent(ren_2.get());

}

EntityManager::~EntityManager() {
    ent_map.clear();
    cmp_storage.~unique_ptr();
}

std::unique_ptr<Entity_t>&
EntityManager::createEntity_t() {
    auto new_ent { std::make_unique<Entity_t>() };
    return ent_map[new_ent->getID()] = std::move(new_ent);
}

} // namespace AIP
