#include <ecs/cmp/CmpVector_t.hpp>

#include <algorithm>

namespace BECS {

template <typename T>
CmpVector<T>::CmpVector() {
    cmps.reserve(MAX_CMP_SIZE);
}

template <typename T>
bool 
CmpVector<T>::deleteCmpByEntityID(entID eid) noexcept {
    auto result = true;
    auto it_cmp = findCmpByEntityID(eid);
    
    if(!it_cmp) 
        result = false;
    else {
        auto it = *it_cmp;

        if( it + 1 != cmps.end() )
            *it = cmps.back();

        cmps.pop_back();
    }

    return result;
}

template <typename T>
auto
CmpVector<T>::findCmpByEntityID(entID eid) noexcept {
    std::optional it_cmp = std::find_if(cmps.begin(), cmps.end(), 
            [&eid](T& cmp) { 
                return cmp.getEntityID() == eid; 
            }
        );
        
    if( it_cmp == cmps.end() )
        it_cmp.reset();

    return it_cmp;
}

}