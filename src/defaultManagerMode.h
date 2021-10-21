#pragma once

#include <chrono>

#include "managerMode.h"
#include "selectShapeCanvasAction.h"

using std::chrono::duration_cast;
using std::chrono::system_clock;
using std::chrono::milliseconds;

class DefaultManagerMode : public ManagerMode {
 private:
  SelectCanvasAction selection;

  int lastTimeClicked = 0;

  int getTime();
public:
  DefaultManagerMode();
  virtual void start(Canvas *canvas);
  virtual void update(Canvas *canvas, InputInfo *inputInfo);
  virtual void stop(Canvas *canvas);
};
