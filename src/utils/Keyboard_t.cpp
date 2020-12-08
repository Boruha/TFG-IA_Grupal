#include <utils/Keyboard_t.hpp>

namespace AIP {

Keyboard_t::OptKeyIt
Keyboard_t::getKeyIterator(KeySym key) noexcept {
    auto it_key = keys.find(key);

    if(it_key != end(keys))
        return it_key;

    return {};
}

bool
Keyboard_t::isKeyPressed(KeySym key) noexcept {
    if( auto it_key = getKeyIterator(key) )
        return (*it_key)->second;

    return false;
}

void
Keyboard_t::setValue(KeySym key, bool value) noexcept {
    if( auto it_key = getKeyIterator(key) )
        (*it_key)->second = value;
}


} //NS