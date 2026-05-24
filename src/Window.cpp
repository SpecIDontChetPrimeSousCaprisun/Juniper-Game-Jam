#include "Window.h"
#include "Object.h"
#include "Player.h"
#include "Container.h"
#include "UIElement.h"
#include "TextElement.h"
#include "Button.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>
#include <iomanip>

// REQUIRED definition (missing in your case)
GLFWwindow* Window::window = nullptr;
double Window::deltaTime = 0;
int Window::fbWidth = 600;
int Window::fbHeight = 480;
bool Window::inGame = true;

double lastFrame = 0.0;
bool toggledMenu = false;
bool resizing = false;

int Window::init() {
  glfwSetErrorCallback([](int error, const char* description) {
      std::cout << "GLFW ERROR: " << description << "\n";
  }); 

  /* Initialize the library */
  if (!glfwInit())
      return -1; 

  glfwWindowHint(GLFW_DEPTH_BITS, 24);

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(fbWidth, fbHeight, "Game", NULL, NULL);

  if (!window)
  {
      glfwTerminate();
      return -1;
  } 

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  glfwSwapInterval(0); 

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD\n";
      return -1;
  }

  glClearColor(0.2f, 0.4f, 0.6f, 1.0f);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glm::mat4 projection = glm::ortho(
      0.0f, (float)fbWidth,
      (float)fbHeight, 0.0f,
      -1.0f, 1.0f
  );
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

  glfwSetFramebufferSizeCallback(window,
  [](GLFWwindow*, int width, int height)
  {
      resizing = (width == 0 || height == 0);
  });

  return 0;
}

void Window::mainLoop() { 
  std::vector<Object*> menuElements;
  
  UIElement* menuBackground = new UIElement(glm::vec2(0.5f, 0.5f), glm::vec2(0.5f, 0.75f), 0.0f, "textures/Wallpaper.jpeg", 1);
  TextElement* nameLabel = new TextElement(glm::vec2(0.5f, 0.1f), glm::vec2(0.5f, 0.1f), 1.0f, "textures/Wallpaper.jpeg", 2, "GAME NAME HERE", "fonts/Kenney Future Narrow.ttf", glm::vec3(0.0f, 0.0f, 0.0f));
  Button* exitButton = new Button(glm::vec2(0.5f, 0.9f), glm::vec2(0.5f, 0.1f), 0.0f, "textures/Wallpaper.jpeg", 2, "Exit", "fonts/Kenney Future Narrow.ttf", glm::vec3(1.0f, 0.0f, 0.0f));

  exitButton->setCallback([]() {
    inGame = false;
  });

  menuBackground->anchorPoint = glm::vec2(0.5f, 0.5f);
  nameLabel->anchorPoint = glm::vec2(0.5f, 0.0f);
  exitButton->anchorPoint = glm::vec2(0.5f, 1.0f);
  menuElements.push_back(menuBackground);
  menuElements.push_back(nameLabel);
  menuElements.push_back(exitButton);

  Container* menu = new Container(menuElements);
  menu->changeVisibility(false);
  
  while (!glfwWindowShouldClose(window) && inGame){
    if (resizing) {
      glfwPollEvents();
      glfwSwapBuffers(window);
      continue;
    }

    glfwPollEvents();

    double currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    double fps = 1.0 / deltaTime;

    if (deltaTime > 0.1) {
      deltaTime = 0.1;
    } 

    std::ostringstream ss;
    ss << std::fixed << std::setprecision(1) << fps;
    std::string fpsString = ss.str();

    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

    if (fbWidth == 0 || fbHeight == 0) {
      glfwSwapBuffers(window);
      continue;
    }

    glViewport(0, 0, fbWidth, fbHeight);

    glClear(GL_COLOR_BUFFER_BIT);
   
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && !toggledMenu) {
      menu->changeVisibility(!menu->objects[0]->visible);
      toggledMenu = true;
    } else if (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
      toggledMenu = false;
    }

    Player::update();
    Object::updateAll();

    Object::drawAll();

    glfwSwapBuffers(window);
  }

  glfwTerminate();
}
