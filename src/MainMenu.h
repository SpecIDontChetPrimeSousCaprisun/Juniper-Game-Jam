#pragma once

#include "Container.h"
#include "TextElement.h"

#include <map>
#include <string>

class MainMenu {
public:
  static void init();
private:
  static void loadLevel(std::string level);
  static void initLevel(std::string level);

  static std::map<std::string, Container*> initializedLevels;
  static Container* UI;
  static Container* levelButtons;
  static Container* loadingUI;
  static TextElement* loadingSpin;
};
