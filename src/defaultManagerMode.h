#pragma once

#include "managerMode.h"
#include "selectShapeCanvasAction.h"

class DefaultManagerMode : public ManagerMode {
 private:
  SelectCanvasAction selection;
public:
  DefaultManagerMode();
  virtual void start(Canvas *canvas);
  virtual void update(Canvas *canvas, InputInfo *inputInfo);
  virtual void stop(Canvas *canvas);
};
