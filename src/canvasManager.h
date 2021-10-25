#pragma once

#include <unordered_map>

#include "canvas.h"
#include "drawManager.h"
#include "inputInfo.h"
#include "managerMode.h"
#include "canvasManagerState.h"
#include "constraintsManagerMode.h"

using std::unordered_map;

enum class ManagerModeEnum {
  DefaultMode,
  PolygonMode,
  CircleMode,
  ConstraintMode,
  NoMode
};

class CanvasManager {
 private:
  unordered_map<ManagerModeEnum, ManagerMode*> modes;
  ManagerModeEnum currMode;
  ManagerModeEnum expectedMode;

  Canvas *canvas;

  CanvasManagerState state;
public:
  CanvasManager(Canvas *_canvas);

  void setMode(ManagerModeEnum newMode);
  ManagerModeEnum getMode();

  Canvas *getCanvas();

  bool canDoAction(ManagerModeEnum expectedMode, int actionID);
  void doAction(ManagerModeEnum expectedMode, int actionID);

  void setup();
  void update(Canvas *canvas, InputInfo *inputInfo);
  void draw(DrawManager *drawManager);

  void setupSomeShapes();
};
