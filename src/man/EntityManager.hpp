#pragma once


#include <man/Manager_t.hpp>

namespace AIP
{  

struct EntityManager : Manager_t
{
    explicit EntityManager();
            ~EntityManager() override;
};

} // namespace AIP