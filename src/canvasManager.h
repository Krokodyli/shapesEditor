#pragma once

#include <unordered_map>

#include "canvas.h"
#include "inputInfo.h"
#include "managerMode.h"

using std::unordered_map;

enum class ManagerModeEnum {
  DefaultMode,
  PolygonMode,
  CircleMode,
  NoMode
};

class CanvasManager {
 private:
  unordered_map<ManagerModeEnum, ManagerMode*> modes;
  ManagerModeEnum currMode;
  ManagerModeEnum expectedMode;

  Canvas *canvas;
public:
  CanvasManager(Canvas *_canvas);

  void setMode(ManagerModeEnum newMode);
  ManagerModeEnum getMode();

  Canvas *getCanvas();

  bool canDoAction(ManagerModeEnum expectedMode, int actionID);
  void doAction(ManagerModeEnum expectedMode, int actionID);

  void setup();
  void update(Canvas *canvas, InputInfo *inputInfo);
};
