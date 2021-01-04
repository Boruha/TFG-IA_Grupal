#include <cmp/CmpVector_t.hpp>

#include <algorithm>

namespace AIP {

template <typename T>
CmpVector<T>::CmpVector() {
    cmps.reserve(10u); 
}

template <typename T>
Component_t* 
CmpVector<T>::deleteCmpByEntityID(entID eid) {
    auto it_cmp = getCmpByID(eid);
    if(!it_cmp) return nullptr;
    
    auto it = *it_cmp;

    if( it + 1 != cmps.end() )
        *it = cmps.back();

    cmps.pop_back();

    return it.base();
}

template <typename T>
auto
CmpVector<T>::getCmpByID(entID eid) noexcept {
    std::optional it_cmp = std::find_if(cmps.begin(), cmps.end(), 
        [&eid](T& cmp) { 
            return cmp.getEntityID() == eid; 
        }
    );
    if( it_cmp == cmps.end() ) it_cmp.reset();

    return it_cmp;
}

}