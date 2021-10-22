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
}

void Toolbar::setup() {
  buttons.push_back(Button("Shape manipulation mode",
                           Point(15, 15), AppConsts::defaultModeButtonImage));
}
