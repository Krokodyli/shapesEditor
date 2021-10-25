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
  Button getConstraintsModeButton();

  Button getDeleteButton();
  Button getInsertVertexButton();

  Button getFixedCenterConstraintButton();
  Button getFixedRadiusConstraintButton();
  Button getFixedLengthConstraintButton();
  Button getEqualEdgesConstraintButton();
  Button getParallelEdgesConstraintButton();
  Button getTangentConstraintButton();
  Button getDeleteConstraintButton();

public:
  Toolbar();
  void update(CanvasManager *canvasManager, InputInfo *inputInfo);
  void draw(DrawManager *drawManager);
};
