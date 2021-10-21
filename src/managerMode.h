#pragma once

#include "canvas.h"
#include "inputInfo.h"

class ManagerMode
{
 public:
  virtual void start(Canvas *canvas) = 0;
  virtual void update(Canvas *canvas, InputInfo *inputInfo) = 0;
  virtual void stop(Canvas *canvas) = 0;
};
