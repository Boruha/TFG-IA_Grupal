#pragma once
#include <game/utils/fvec2.hpp>
#include <array>

namespace AIP {

struct Patrol_t {
    using Point2D_t = fvec2<fint_t<int64_t>>;

    static const std::size_t sz { 4u };
    std::array<Point2D_t, sz> points { };
    
    struct iterator {
        bool operator==(iterator const& oIt)
            { return index == oIt.index; }

        bool operator!=(iterator const& oIt)
            { return index != oIt.index; }

        void operator++() 
            { index = (index+1) % sz; }

        Point2D_t& operator*()
            { return (*point_ptr)[index]; }
        
        std::size_t index { 0u };
        std::array<Point2D_t, sz>* point_ptr { nullptr };
    };

    iterator begin() { return { 0 , &points }; }
    iterator end()   { return { sz, &points }; }
};

} //NS