#pragma once

#include <iostream>
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>

class Window {
public:
  static int init();
  static void mainLoop();
  static GLFWwindow* window;

  static double deltaTime;
  static int fbWidth, fbHeight;
};
