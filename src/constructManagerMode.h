#pragma once

#include "managerMode.h"
#include "constructCanvasAction.h"

class ConstructManagerMode : public ManagerMode {
 private:
  createConstructionFunc createShapeFunc;
  ConstructCanvasAction constructAction;
public:
  ConstructManagerMode(createConstructionFunc _createShapeFunc, Canvas *canvas);
  virtual void start(Canvas *canvas);
  virtual void update(Canvas *canvas, InputInfo *inputInfo);
  virtual void stop(Canvas *canvas);
};
