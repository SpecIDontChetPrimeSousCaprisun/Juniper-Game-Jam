#include "Tutorial.h"
#include "Window.h"
#include "Player.h"

#include <cmath>

Tutorial* Tutorial::currentTutorial = nullptr;

Tutorial::Tutorial() : Object(glm::vec2(0.0f, -1000.0f), glm::vec2(100.0f, 100.0f), 0.0f, "textures/player.png", -1) {
  anchored = true;
  canCollide = false;
  currentTutorial = this;
}

void Tutorial::update() {
  if (currentTutorial == nullptr) return;

  if (currentTutorial->position.y < 25) {
    currentTutorial->position.y += 500 * Window::deltaTime;
  } else {
    if (currentTutorial->position.x > Player::currentPlayer->position.x) {
      currentTutorial->position.x -= 200 * Window::deltaTime; 
    } else if (currentTutorial->position.x < Player::currentPlayer->position.x) {
      currentTutorial->position.x += 200 * Window::deltaTime; 
    }
  }
}
