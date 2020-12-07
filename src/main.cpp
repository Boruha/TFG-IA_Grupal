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
      lastUpdateTime = time.now();
      gameCondition  = gameManager->update();
    }
  }

  //cuando me ponga con el delta time mirar de dejar esto más bonito con funciones que te den el reloj, delta time y demases.

  return 0;
}