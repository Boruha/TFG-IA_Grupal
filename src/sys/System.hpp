#pragma once

namespace AIP {

struct System {
    virtual ~System() = default;
    
    virtual void init()   = 0;
    virtual bool update() = 0;
};

}