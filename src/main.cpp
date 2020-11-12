#include <main.hpp>

#include <man/GameManager.hpp>

#include <utils/GameConstants.hpp>

#include <memory>

int main() {
  using timer = std::chrono::steady_clock;

  auto  gameManager    { std::make_unique<AIP::GameManager>() };
  bool  gameCondition  { true };
  timer time           { };
  auto  lastUpdateTime { time.now() };
  auto  timeElapse     { std::chrono::microseconds { 0 } };

  while (gameCondition) {
    timeElapse = std::chrono::duration_cast<std::chrono::microseconds>(time.now() - lastUpdateTime);

    if(timeElapse.count() >= AIP::DELTATIME_MICRO.number) {
      gameCondition  = gameManager->update();
      lastUpdateTime = time.now();
    }
  }
  
  gameManager.~unique_ptr();

  return 0;
}