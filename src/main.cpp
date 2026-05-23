#include "Window.h"
#include "Object.h"
#include "Player.h"
#include "Sound.h"
#include "UIElement.h"
#include "TextElement.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
  if (Window::init() == -1) return -1;      

  Sound::init();
  Object::initShader();
  TextElement::initShader();

  new Player(glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f), 0.0f, "textures/Wallpaper.jpeg", 2, true);
  Object* obj2 = new Object(glm::vec2(300.0f, 0.0f), glm::vec2(100.0f, 100.0f), 0.0f, "textures/Wallpaper.jpeg", 2);
  Object* platform = new Object(glm::vec2(0.0f, 500.0f), glm::vec2(10000.0f, 10000000.0f), 0.0f, "textures/Wallpaper.jpeg", 1);

  obj2->anchored = false;
  obj2->canCollide = true;
  obj2->linearVelocity = glm::vec2(-100.f, 0.0f);

  platform->canCollide = true;
 
  Window::mainLoop();
  Sound::unInit();
}
