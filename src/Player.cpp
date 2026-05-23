#include "Player.h"
#include "Window.h"

Player* Player::currentPlayer;

Player::Player(glm::vec2 position, glm::vec2 size, float transparency, std::string texPath, int zIndex, bool isCurrentPlayer) 
  : Object(position, size, transparency, texPath, zIndex) {
  anchored = false;
  canCollide = true;

  if (isCurrentPlayer) currentPlayer = this;
}

void Player::update() {
  if (!currentPlayer) return;

  glm::vec2 hitPoint;
  float tHit;
  std::vector<Object*> ignore;

  ignore.push_back(currentPlayer);

  Object* result = Object::raycast(
    currentPlayer->position + glm::vec2(currentPlayer->size.x / 2, 0.0f),
    glm::vec2(0.0f, 5.0f + currentPlayer->size.y),
    hitPoint,
    tHit,
    ignore
  );

  if (glfwGetKey(Window::window, GLFW_KEY_SPACE) == GLFW_PRESS && result) {
    currentPlayer->linearVelocity -= glm::vec2(0.0f, 10.0f);
  }

  if (glfwGetKey(Window::window, GLFW_KEY_D) == GLFW_PRESS) {
    currentPlayer->linearVelocity.x = 250.0f;
  } else if (glfwGetKey(Window::window, GLFW_KEY_A) == GLFW_PRESS) {
    currentPlayer->linearVelocity.x = -250.0f;
  } else {
    currentPlayer->linearVelocity.x = 0.0f;
  }
}
