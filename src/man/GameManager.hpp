#pragma once
#include <vector>
#include <memory>

namespace AIP {

struct System_t;
struct Manager_t;

struct GameManager {
    explicit GameManager();
            ~GameManager();

    bool update() noexcept;

private:
    std::vector<std::unique_ptr<System_t>> systems;
    std::unique_ptr<Manager_t> manager;
};

}
