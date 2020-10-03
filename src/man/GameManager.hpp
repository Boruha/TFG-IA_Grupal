#pragma once

#include <vector>
#include <memory>

namespace AIP {

struct Entity_t;
struct System_t;
struct Manager_t;

struct GameManager {
    explicit GameManager();
            ~GameManager();

    bool update();

private:
    std::vector<std::unique_ptr<System_t>> systems;
    std::unique_ptr<Manager_t> manager;
};

}