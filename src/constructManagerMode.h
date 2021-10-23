#pragma once

#include "managerMode.h"
#include "constructCanvasAction.h"

class ConstructManagerMode : public ManagerMode {
 private:
  createConstructionFunc createShapeFunc;
  ConstructCanvasAction constructAction;

public:
  ConstructManagerMode(CanvasManagerState *_state,
                       createConstructionFunc _createShapeFunc, Canvas *canvas);

  virtual void start(Canvas *canvas);
  virtual void update(Canvas *canvas, InputInfo *inputInfo);
  virtual void stop(Canvas *canvas);

  virtual void doAction(Canvas *canvas, int actionID);
  virtual bool canDoAction(Canvas *canvas, int actionID);

  virtual void draw(DrawManager *drawManager, Canvas *canvas);
};
