#include <man/EntityManager.hpp>
#include <ent/Entity_t.hpp>

namespace AIP {

constexpr const uint32_t MAX_ENTITIES { 10 };

EntityManager::EntityManager() {
    ent_vector.reserve(MAX_ENTITIES);

    createEntity_t(10U, 10U);
    createEntity_t(100U, 300U);
}

EntityManager::~EntityManager() {
    ent_vector.clear();
}

void
EntityManager::createEntity_t(const uint32_t coord_X, const uint32_t coord_Y) {
    ent_vector.emplace_back( std::make_unique<Entity_t>(coord_X, coord_Y, 15U, 20U, Color::Black) ); //Cambiar a parámetros;
}

} // namespace AIP
