#include <man/EntityManager.hpp>

#include <ent/Entity_t.hpp>
#include <ent/Flock_t.hpp>

#include <cmp/MovementComponent.hpp>
#include <cmp/RenderComponent.hpp>

namespace AIP {

constexpr const uint32_t MAX_ENTITIES { 10 };

EntityManager::EntityManager() {
    flock_vec.reserve(1);

    auto& flock_1 = createFlock_t();
    /*ent 1*/
    auto& ent1  = createEntity_t();
    auto& mov_1 = cmp_storage->createComponent( MovementComponent(ent1->getID(), 30U, 30U) );
    auto& ren_1 = cmp_storage->createComponent( RenderComponent(ent1->getID(), 10U, 10U, Color::White) );
    auto& ai_1  = cmp_storage->createComponent( AI_Component(ent1->getID()) );

    ent1->addComponent(mov_1.get());
    ent1->addComponent(ren_1.get());
    ent1->addComponent(ai_1.get());

    flock_1->squadron.emplace_back(ent1.get());
    /*ent 2*/
    auto& ent2  = createEntity_t();
    auto& mov_2 = cmp_storage->createComponent( MovementComponent(ent2->getID(), 100U, 100U) );
    auto& ren_2 = cmp_storage->createComponent( RenderComponent(ent2->getID(), 10U, 10U, Color::Green) );
    auto& ai_2  = cmp_storage->createComponent( AI_Component(ent2->getID()) );

    ent2->addComponent(mov_2.get());
    ent2->addComponent(ren_2.get());
    ent2->addComponent(ai_2.get());

    flock_1->squadron.emplace_back(ent2.get());
    /*ent 3*/
    auto& ent3  = createEntity_t();
    auto& mov_3 = cmp_storage->createComponent( MovementComponent(ent3->getID(), 100U, 200U) );
    auto& ren_3 = cmp_storage->createComponent( RenderComponent(ent3->getID(), 10U, 10U, Color::Blue) );
    auto& ai_3  = cmp_storage->createComponent( AI_Component(ent3->getID()) );

    ent3->addComponent(mov_3.get());
    ent3->addComponent(ren_3.get());
    ent3->addComponent(ai_3.get());

    flock_1->squadron.emplace_back(ent3.get());
    /*ent 4*/
    auto& ent4  = createEntity_t();
    auto& mov_4 = cmp_storage->createComponent( MovementComponent(ent4->getID(), 200U, 200U) );
    auto& ren_4 = cmp_storage->createComponent( RenderComponent(ent4->getID(), 10U, 10U, Color::Blue) );
    auto& ai_4  = cmp_storage->createComponent( AI_Component(ent4->getID()) );

    ent4->addComponent(mov_4.get());
    ent4->addComponent(ren_4.get());
    ent4->addComponent(ai_4.get());

    flock_1->squadron.emplace_back(ent4.get());

}

EntityManager::~EntityManager() {
    ent_map.clear();
    flock_vec.clear();
    cmp_storage.~unique_ptr();
}

std::unique_ptr<Entity_t>&
EntityManager::createEntity_t() noexcept {
    auto new_ent { std::make_unique<Entity_t>() };
    return ent_map[new_ent->getID()] = std::move(new_ent);
}

std::unique_ptr<Flock_t>&  
EntityManager::createFlock_t() noexcept {
    return flock_vec.emplace_back( std::make_unique<Flock_t>() );
}


} // namespace AIP
