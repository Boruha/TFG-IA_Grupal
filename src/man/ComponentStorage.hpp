#pragma once
#include <vector>
#include <memory>
#include <unordered_map>


namespace AIP {

//Struct generico para nuestras temp de Cmps
struct Cmp_Collection {
    virtual ~Cmp_Collection() = default;
};

//Vector que se creará por cada Cmp
template<typename T>
struct Cmp_Vector : Cmp_Collection {
    ~Cmp_Vector<T>() override = default;
    std::vector<T> cmps;
};


struct ComponentStorage
{
    explicit ComponentStorage() = default;
             
               ComponentStorage(const ComponentStorage& ) = delete; //1 '&' = LValue, 2 '&' = RValue (Valor temporal)
               ComponentStorage(const ComponentStorage&&) = delete;
    ComponentStorage& operator=(const ComponentStorage& ) = delete;
    ComponentStorage& operator=(const ComponentStorage&&) = delete;

private:
    //Contendrá <ID unico de cmpType, Coleccion de Cmps de ese tipo >
    std::unordered_map<std::size_t , std::unique_ptr<Cmp_Collection>> Cmp_map;
};

}