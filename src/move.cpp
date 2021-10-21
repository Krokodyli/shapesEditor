#include "move.h"

Move::Move() { }

Move::Move(Point _oldMousePos, Point _newMousePos) {
  oldMousePos = _oldMousePos;
  newMousePos = _newMousePos;
  delta = _newMousePos - _oldMousePos;
}
