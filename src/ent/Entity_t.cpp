#include <ent/Entity_t.hpp>

namespace AIP {

Entity_t::Entity_t(uint32_t c_X, uint32_t c_Y, uint32_t s_W, uint32_t s_H) 
    : coord_X(c_X), coord_Y(c_Y), sprite_W(s_W), sprite_H(s_H), entID(++counterID) {
    sprite.reserve(s_W * s_H);
}
    
} // namespace AIP
