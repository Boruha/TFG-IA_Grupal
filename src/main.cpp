#include <main.hpp>
#include <memory>

#include <man/GameManager.hpp>
#include <utils/GameConstants.hpp>

int main() {
  using timer = std::chrono::steady_clock;

  auto  gameManager    { std::make_unique<AIP::GameManager>() };
  bool  gameCondition  { true };
  timer time           { };
  auto  lastUpdateTime { time.now() };
  auto  timeElapse     { std::chrono::milliseconds { 0 } };

  while (gameCondition) {
    timeElapse = std::chrono::duration_cast<std::chrono::milliseconds>(time.now() - lastUpdateTime);

    if(timeElapse >= DELTATIME) {
      gameCondition  = gameManager->update();
      lastUpdateTime = time.now();
    }
  }
  
  gameManager.~unique_ptr();

  return 0;
}