#include "MainMenu.h"
#include "Button.h"
#include "Player.h"

std::map<std::string, Container*> MainMenu::initializedLevels;
Container* MainMenu::UI;
Container* MainMenu::levelButtons;
Container* MainMenu::loadingUI;
TextElement* MainMenu::loadingSpin;

void MainMenu::init() {
  std::vector<Object*> UIElements;

  TextElement* title = new TextElement(glm::vec2(0.5f, 0.15f), glm::vec2(0.75f, 0.1f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 20,
                                       "ANGULAR VELOCITY", "fonts/Kenney Future Narrow.ttf", glm::vec3(1.0f, 1.0f, 1.0f));
  Button* levelsButton = new Button(glm::vec2(0.5f, 0.65f), glm::vec2(0.25f, 0.075f), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 20,
                                    "Levels", "fonts/Kenney Future Narrow.ttf", glm::vec3(1.0f, 1.0f, 1.0f));

  title->anchorPoint = glm::vec2(0.5f, 0.0f);
  title->angularVelocity = 250.0f;

  levelsButton->anchorPoint = glm::vec2(0.5f, 0.0f);
  levelsButton->cornerRadius = 0.025f;
  levelsButton->setHoverCallback([levelsButton](bool hovered) {
    if (hovered) {
      levelsButton->angularVelocity = 100.0f;
    } else {
      levelsButton->angularVelocity = 0.0f;
      levelsButton->rotation = 0.0f;
    }
  });
  levelsButton->setCallback([]() {
    UI->changeVisibility(false);
    levelButtons->changeVisibility(true);
  });

  UIElements.push_back(title);
  UIElements.push_back(levelsButton);

  UI = new Container(UIElements);
  UI->changeVisibility(true);
  UI->registerObjects();

  // Levels
  std::vector<Object*> levelUI;

  Button* tutorialButton = new Button(glm::vec2(0.5f, 0.65f), glm::vec2(0.25f, 0.075f), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 20,
                                      "Tutorial", "fonts/Kenney Future Narrow.ttf", glm::vec3(1.0f, 1.0f, 1.0f));

  tutorialButton->anchorPoint = glm::vec2(0.5f, 0.0f);
  tutorialButton->cornerRadius = 0.025f;
  tutorialButton->setHoverCallback([tutorialButton](bool hovered) {
    if (hovered) {
      tutorialButton->angularVelocity = 100.0f;
    } else {
      tutorialButton->angularVelocity = 0.0f;
      tutorialButton->rotation = 0.0f;
    }
  });
  tutorialButton->setCallback([]() {
    loadLevel("Tutorial");
  });

  levelUI.push_back(tutorialButton);

  levelButtons = new Container(levelUI);
  levelButtons->changeVisibility(false);
  levelButtons->registerObjects();

  // Loading
  std::vector<Object*> loadingUIElements;

  TextElement* spinnyThing = new TextElement(glm::vec2(0.5f, 0.15f), glm::vec2(0.75f, 0.1f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 20,
                                             "If i'm not spinning there's a problem", "fonts/Kenney Future Narrow.ttf", glm::vec3(1.0f, 1.0f, 1.0f));
  loadingSpin = new TextElement(glm::vec2(0.5f, 0.75f), glm::vec2(0.75f, 0.1f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), 20,
                                "Full revolution = loaded", "fonts/Kenney Future Narrow.ttf", glm::vec3(1.0f, 1.0f, 1.0f));
  UIElement* loadingBackground = new UIElement(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 19);

  spinnyThing->anchorPoint = glm::vec2(0.5f, 0.5f);
  spinnyThing->angularVelocity = 150;

  loadingSpin->anchorPoint = glm::vec2(0.5f, 0.5f);

  loadingUIElements.push_back(spinnyThing);
  loadingUIElements.push_back(loadingSpin);
  loadingUIElements.push_back(loadingBackground);

  loadingUI = new Container(loadingUIElements);
  loadingUI->changeVisibility(false);
  loadingUI->registerObjects();
}

void MainMenu::loadLevel(std::string level) {
  UI->changeVisibility(false);
  levelButtons->changeVisibility(false);
  loadingUI->changeVisibility(true);

  if (!initializedLevels[level]) initLevel(level);

  Player* plr = new Player(glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f), 0.0f, "textures/player.png", 2, true);
  plr->registerObject();

  initializedLevels[level]->changeCollisions(true);
  initializedLevels[level]->changeVisibility(true);
  loadingUI->changeVisibility(false);
}

void MainMenu::initLevel(std::string level) {
  std::vector<Object*> objects;

  if (level == "Tutorial") { 
    Object* obj2 = new Object(glm::vec2(300.0f, 0.0f), glm::vec2(100.0f, 1000.0f), 0.0f, "textures/box.png", 2);
    Object* platform = new Object(glm::vec2(-500.0f, 500.0f), glm::vec2(1000.0f, 1000.0f), 0.0f, "textures/Wallpaper.jpeg", 1);

    //enemy->registerObject();

    //obj2->anchored = false;
    obj2->canCollide = true;
    obj2->linearVelocity = glm::vec2(-100.f, 0.0f);
    obj2->rotation = 0;
    obj2->angularVelocity = 50.0f;
    //obj2->registerObject();

    platform->canCollide = true;
    platform->rotation = 15;
  
    objects.push_back(platform);
  }

  Container* lvl = new Container(objects);
  lvl->changeVisibility(false);
  lvl->changeCollisions(false);
  lvl->registerObjects();
  initializedLevels[level] = lvl;
}
