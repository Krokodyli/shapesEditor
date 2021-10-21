#pragma once

#include "point.h"

struct Move {
  Point oldMousePos;
  Point newMousePos;
  Point delta;

  Move();
  Move(Point _oldMousePos, Point _newMousePos);
};
