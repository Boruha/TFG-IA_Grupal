#pragma once
#include <man/Manager_t.hpp>

#include <sys/System_t.hpp>

#include <utils/ufixed64_t.hpp>

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
    
    fixed64_t getLoopTime()  noexcept;
    fixed64_t getDeltaTime() noexcept;

private:
    std::vector<std::unique_ptr<System_t>> systems;
    std::unique_ptr<Manager_t> manager;

    fixed64_t setLoopTime()  noexcept;
    fixed64_t setDeltaTime() noexcept;
    void checkFpsMsg()       noexcept;   
    void changeLoopTime(bool operation)  noexcept;
    void changeDeltaTime(bool operation) noexcept;
    
    //TimeInfo
    float FPS_LT { 60.f };
    float FPS_DT { 60.f };
    const float Micro_multi { 1000000.f };
    fixed64_t LoopTime  { setLoopTime() };
    fixed64_t DeltaTime { setDeltaTime() };

};

}
