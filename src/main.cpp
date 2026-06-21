#include "Window.h"
#include "Object.h"
#include "Player.h"
#include "Sound.h"
#include "UIElement.h"
#include "TextElement.h"
#include "Enemy.h"
#include "MainMenu.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {
  Sound::init();

  if (Window::init() == -1) return -1;      
 
  Object::initShader();
  TextElement::initShader();
  MainMenu::init();
 
  Window::mainLoop();
  Sound::unInit();
}
