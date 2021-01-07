#include <main.hpp>

#include <game/man/GameManager.hpp>

#include <memory>
#include <chrono>

int main() {
  using timer = std::chrono::steady_clock;

  AIP::GameManager gameManager { };
  bool  gameCondition  { true };

  //glock
  timer time           { };
  auto  lastUpdateTime { time.now() };
  auto  timeElapse     { std::chrono::microseconds { 0 } };

  while (gameCondition) {
    timeElapse = std::chrono::duration_cast<std::chrono::microseconds>(time.now() - lastUpdateTime);

    if(timeElapse.count() >= gameManager.getLoopTime().number) {
      lastUpdateTime = time.now();
      gameCondition  = gameManager.update();
    }
  }

  //cuando me ponga con el delta time mirar de dejar esto más bonito con funciones que te den el reloj, delta time y demases.

  return 0;
}