#include "toolbar.h"
#include "canvas.h"
#include "canvasManager.h"
#include <iostream>

Toolbar::Toolbar() {
  setup();
}

void Toolbar::update(CanvasManager *canvasManager, InputInfo *inputInfo) {
  for (auto &button : buttons)
    button.update(canvasManager, inputInfo);
}

void Toolbar::draw(DrawManager *drawManager){
  drawManager->drawRect(0, 0, AppConsts::toolbarWidth,
                        AppConsts::appSize.y, AppConsts::toolbarColor);
  for(auto &button : buttons)
    button.draw(drawManager);

  for (auto &button : buttons) {
    if(button.isMouseHovering()) {
      drawManager->drawText(button.getDescription(), 15, 35, 15, Color(0, 0, 0)); // TODO
      break;
    }
  }
  drawManager->drawRect(15, 5, 165, 25, Color(170, 255, 170)); // TODO
  drawManager->drawText("Shapes Editor", 20, 5, 20, Color(0, 0, 0));
}

void Toolbar::setup() {
  buttons.push_back(getDefaultModeButton());
  buttons.push_back(getPolygonModeButton());
  buttons.push_back(getCircleModeButton());
}

Button Toolbar::getDefaultModeButton() {
  Button button("Shape manipulation\nmode", Point(33, 100),
                AppConsts::defaultModeButtonImage);
  button.setActionFunc([](CanvasManager *manager) {
    if(manager->getMode() != ManagerModeEnum::DefaultMode)
      manager->setMode(ManagerModeEnum::DefaultMode);
  });
  button.setActiveStatusFunc([](CanvasManager *manager) {
    return manager->getMode() == ManagerModeEnum::DefaultMode;
  });
  return button;
}

Button Toolbar::getPolygonModeButton() {
  Button button("Polygon insertion\nmode", Point(116, 100),
                AppConsts::polygonModeButtonImage);
  button.setActionFunc([](CanvasManager *manager) {
    if (manager->getMode() != ManagerModeEnum::PolygonMode)
      manager->setMode(ManagerModeEnum::PolygonMode);
  });
  button.setActiveStatusFunc([](CanvasManager *manager) {
    return manager->getMode() == ManagerModeEnum::PolygonMode;
  });
  return button;
}

Button Toolbar::getCircleModeButton() {
  Button button("Circle insertion\nmode", Point(33, 180),
                AppConsts::circleModeButtonImage);
  button.setActionFunc([](CanvasManager *manager) {
    if (manager->getMode() != ManagerModeEnum::CircleMode)
      manager->setMode(ManagerModeEnum::CircleMode);
  });
  button.setActiveStatusFunc([](CanvasManager *manager) {
    return manager->getMode() == ManagerModeEnum::CircleMode;
  });
  return button;
}
