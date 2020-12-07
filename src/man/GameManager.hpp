#pragma once

#include <man/Manager_t.hpp>
#include <sys/System_t.hpp>
#include <vector>
#include <memory>

namespace AIP {

struct GameManager {
    explicit GameManager();

    GameManager(const GameManager& )            = delete;
    GameManager(const GameManager&&)            = delete;
    GameManager& operator=(const GameManager& ) = delete;
    GameManager& operator=(const GameManager&&) = delete;

    bool update() noexcept;

private:
    std::vector<std::unique_ptr<System_t>> systems;
    std::unique_ptr<Manager_t> manager;
};

}
