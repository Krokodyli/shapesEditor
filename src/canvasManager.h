#pragma once

#include <unordered_map>

#include "canvas.h"
#include "inputInfo.h"
#include "managerMode.h"

using std::unordered_map;

enum class ManagerModeEnum {
  DefaultMode,
  NoMode
};

class CanvasManager {
 private:
  unordered_map<ManagerModeEnum, ManagerMode*> modes;
  ManagerModeEnum currMode;
  ManagerModeEnum expectedMode;
public:
  CanvasManager();

  void setMode(ManagerModeEnum newMode);
  ManagerModeEnum getMode();

  void setup();
  void update(Canvas *canvas, InputInfo *inputInfo);
};
