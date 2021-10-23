#pragma once

#include "canvas.h"
#include "inputInfo.h"
#include "canvasManagerState.h"

class ManagerMode
{
 protected:
  CanvasManagerState *state;
 public:
  ManagerMode(CanvasManagerState *_state);
  virtual void start(Canvas *canvas) = 0;
  virtual void update(Canvas *canvas, InputInfo *inputInfo) = 0;
  virtual void stop(Canvas *canvas) = 0;

  virtual void doAction(Canvas *canvas, int actionID) = 0;
  virtual bool canDoAction(Canvas *canvas, int actionID) = 0;

  virtual void draw(DrawManager *drawManager, Canvas *canvas) = 0;
};
