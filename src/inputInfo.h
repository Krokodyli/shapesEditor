#pragma once

#include "point.h"

class InputInfo {
 public:
  virtual ~InputInfo();

  virtual void update() = 0;

  virtual bool isLeftPressed() = 0;
  virtual bool isRightPressed() = 0;
  virtual bool wasLeftPressed() = 0;
  virtual bool wasRightPressed() = 0;
  virtual bool isLeftClicked() = 0;
  virtual bool isRightClicked() = 0;

  virtual Point getMousePos() = 0;
  virtual Point getPrevMousePos() = 0;

  virtual Point getOffset() = 0;
  virtual void setOffset(Point _offset) = 0;
};
