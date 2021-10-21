#pragma once

#include "managerMode.h"

class DefaultManagerMode : public ManagerMode {
public:
  virtual void start(Canvas *canvas);
  virtual void update(Canvas *canvas, InputInfo *inputInfo);
  virtual void stop(Canvas *canvas);
};
