#include <man/EntityManager.hpp>

#include <ent/Entity_t.hpp>

#include <utils/AI_Constants.hpp>

namespace AIP {

constexpr const uint32_t MAX_ENTITIES { 10u };

EntityManager::EntityManager() {
    /*ent 1*/
    auto& ent1  = createEntity_t();
    auto& mov_1 = cmp_storage->createComponent( MovementComponent(ent1->getID(), fixed32_t(30) , fixed32_t(30) ) );
    auto& ren_1 = cmp_storage->createComponent( RenderComponent(ent1->getID(), ufixed32_t(10u), ufixed32_t(10u), Color::White) );
    auto& ai_1  = cmp_storage->createComponent( AI_Component(ent1->getID()) );

    ent1->addComponent(mov_1.get());
    ent1->addComponent(ren_1.get());
    ent1->addComponent(ai_1.get());

    /*ent 5 - player*/
    auto& ent5  = createEntity_t();
    auto& mov_5 = cmp_storage->createComponent( MovementComponent(ent5->getID(), fixed32_t(200) , fixed32_t(200)) );
    auto& ren_5 = cmp_storage->createComponent( RenderComponent(ent5->getID(), ufixed32_t(10u), ufixed32_t(10u), Color::Blue) );
    auto& in_5  = cmp_storage->createComponent( InputComponent(ent5->getID()) );

    ent5->addComponent(mov_5.get());
    ent5->addComponent(ren_5.get());
    ent5->addComponent(in_5.get());

    player_id = ent5->getID();
}

EntityManager::~EntityManager() {
    ent_map.clear();
    cmp_storage.~unique_ptr();
}

std::unique_ptr<Entity_t>&
EntityManager::createEntity_t() noexcept {
    auto new_ent { std::make_unique<Entity_t>() };
    return ent_map[new_ent->getID()] = std::move(new_ent);
}

} // namespace AIP
