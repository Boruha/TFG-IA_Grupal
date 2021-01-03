#include <cmp/CmpVector_t.hpp>

namespace AIP {

template<typename T>
CmpVector<T>::CmpVector() {
    cmps.reserve(10u); 
}

template<typename T>
void 
CmpVector<T>::deleteCmpByEntityID(entID eid) {
    auto it_cmp = std::find_if(cmps.begin(), cmps.end(), 
        [&eid](std::unique_ptr<T>& cmp) { 
            return cmp->getEntityID() == eid; 
        }
    );

    if( it_cmp == cmps.end() ) return; //MAMAMAMAMAAAL
    cmps.erase(it_cmp);
}

}