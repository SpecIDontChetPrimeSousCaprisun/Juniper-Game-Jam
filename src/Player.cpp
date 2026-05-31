#include "Player.h"
#include "Window.h"
#include "Particle.h"
#include "Sound.h"
#include "UIParticle.h"

#include <cmath>
#include <thread>

Player* Player::currentPlayer;
UIElement* Player::healthBar;
UIElement* Player::healthBarBackground;

Player::Player(glm::vec2 position, glm::vec2 size, float transparency, std::string texPath, int zIndex, bool isCurrentPlayer) 
  : Object(position, size, transparency, texPath, zIndex), health(100), maxHealth(100) {
  anchored = false;
  canCollide = true;

  if (isCurrentPlayer) currentPlayer = this;
}

void Player::update() {
  if (!currentPlayer) return;
  if (!healthBar) {
    healthBar = new UIElement(glm::vec2(0.02f, 0.98f), glm::vec2(0.33f, 0.03f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), 2);
    healthBar->anchorPoint = glm::vec2(0.0f, 1.0f);
    healthBar->registerObject();

    healthBarBackground = new UIElement(glm::vec2(0.01f, 0.99f), glm::vec2(0.35f, 0.05f), 0.25f, glm::vec3(0.25f, 0.25f, 0.25f), 1);
    healthBarBackground->anchorPoint = glm::vec2(0.0f, 1.0f);
    healthBarBackground->registerObject();
  } else {
    healthBar->size.x = std::max((currentPlayer->health / currentPlayer->maxHealth) * 0.33f, 0.0f);
  }

  glm::vec2 hitPoint;
  float tHit;
  std::vector<Object*> ignore;

  ignore.push_back(currentPlayer);

  Object* result = Object::raycast(
    currentPlayer->position + glm::vec2(currentPlayer->size.x / 2, 0.0f),
    glm::vec2(0.0f, 0.01f + currentPlayer->size.y),
    hitPoint,
    tHit,
    ignore
  );

  if (glfwGetKey(Window::window, GLFW_KEY_SPACE) == GLFW_PRESS && result) {
    currentPlayer->linearVelocity -= glm::vec2(0.0f, 400.0f);
  
    glm::vec2 particlePos = currentPlayer->position;
    particlePos += glm::vec2(currentPlayer->size.x / 2, currentPlayer->size.y);

    Sound::playSound("sfx/jump.wav");
    Particle::createParticles(particlePos, glm::vec2(25.0f, 25.0f), 0.5f, "textures/Wallpaper.jpeg", glm::vec2(0.0f, -100.0f), 100.0f, 5.0f, 10);
  }

  if (glfwGetKey(Window::window, GLFW_KEY_D) == GLFW_PRESS) {
    currentPlayer->linearVelocity.x = 250.0f;
  } else if (glfwGetKey(Window::window, GLFW_KEY_A) == GLFW_PRESS) {
    currentPlayer->linearVelocity.x = -250.0f;
  } else {
    currentPlayer->linearVelocity.x = 0.0f;
  }

  if (currentPlayer->position.y >= 5000.0f) {
    currentPlayer->position = glm::vec2(0.0f, 0.0f);
  }
}

float Player::getHealth() {
  return health;
}

void Player::takeDamage(float damage) {
  health -= damage;
  colorChange.x = 1.0f;

  if (!(this == currentPlayer)) return;

  glm::vec2 particlePos(healthBar->position.x + std::max((currentPlayer->health / currentPlayer->maxHealth) * 0.33f, 0.0f), healthBar->position.y - (healthBar->size.y / 2));
  UIParticle::createParticles(particlePos, glm::vec2(0.01f, 0.01f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.1f, 0.0f), 0.1f, 5.0f, 10);
}

void Player::setHealth(float health) {
  this->health = health;
}

void Player::beforeUpdate() {
  colorChange.x -= 1.0f * Window::deltaTime;
}
