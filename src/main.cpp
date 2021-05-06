#include <main.hpp>

#include <game/man/GameManager.hpp>
#include <game/utils/GameConditions.hpp>

#include <chrono>
#include <iostream>

int main() {
  using timer = std::chrono::steady_clock;

  AIP::GameManager gameManager   { };
  GameConditions   gameCondition { GameConditions::Loop };

  //glock
  timer time           { };
  auto  lastUpdateTime { time.now() };
  auto  timeElapse     { std::chrono::microseconds { 0 } };

  while (gameCondition != GameConditions::Cerrar) {
    timeElapse = std::chrono::duration_cast<std::chrono::microseconds>(time.now() - lastUpdateTime);

    if(timeElapse.count() >= gameManager.getLoopTime().number) {
      lastUpdateTime = time.now();
      gameCondition  = gameManager.update();
    }

    if(gameCondition == GameConditions::Victoria) {
      gameManager.clear();
      gameManager.loadLevel1();
      gameCondition = GameConditions::Loop;
    }

    if(gameCondition == GameConditions::Derrota) {
      gameManager.clear();
      gameManager.loadLevel0();
      gameCondition = GameConditions::Loop;
    }
  }
  
  return 0;
}