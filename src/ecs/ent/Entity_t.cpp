#include <ecs/ent/Entity_t.hpp>


namespace BECS {


Entity_t::Entity_t() : ent_id(++counterID) { }

void 
Entity_t::addComponent(cmpTypeID cmpType) noexcept {
    cmp_types.emplace_back(cmpType);
}

std::vector<cmpTypeID>&
Entity_t::getComponentsType() noexcept { return cmp_types; }

const entID
Entity_t::getID() const noexcept { return ent_id; }


} //NS