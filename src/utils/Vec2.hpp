#pragma once
#include <cmath>

namespace AIP {

template<typename T>
struct Vec2 {
    Vec2<T>() = default;
    Vec2<T>(const T  X,  const T  Y ) : x(X), y(Y) { }
    //Añadir cstor de copia y move

    T x { };
    T y { };

    T length() {
        return std::sqrt( (x*x) + (y*y) ); //TODO: guardar el valor y renovar al cambiar alguna de las componentes.
    }

    void normalize() {
        auto module = length();
        if(module != 0) {
            x /= module;
            y /= module;
        }
        else
        {
            x = 0;
            y = 0;
        }
        
    }
};

}// NS
