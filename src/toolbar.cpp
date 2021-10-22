#include "toolbar.h"
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
  buttons.push_back(Button("Shape manipulation\nmode",
                           Point(15, 100), AppConsts::defaultModeButtonImage));
}
