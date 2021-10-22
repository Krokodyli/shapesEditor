#pragma once

#include <vector>

#include "drawManager.h"
#include "appConsts.h"
#include "button.h"

using std::vector;

class Toolbar {
  vector<Button> buttons;

  void setup();

  Button getDefaultModeButton();
  Button getPolygonModeButton();
  Button getCircleModeButton();

  Button getDeleteButton();
  Button getInsertVertexButton();
public:
  Toolbar();
  void update(CanvasManager *canvasManager, InputInfo *inputInfo);
  void draw(DrawManager *drawManager);
};
