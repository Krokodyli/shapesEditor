#pragma once

#include <vector>

#include "move.h"
#include "canvasAction.h"
#include "selectShapeCanvasAction.h"

using std::vector;

class Shape;

class MoveCanvasAction : public CanvasAction {
 private:
  Move moveValue;
  vector<Shape*> shapes;
  vector<ShapePart*> shapeParts;

public:
  void move(SelectCanvasAction *selectAction, Move _move);

  virtual void doAction(std::vector<Shape *> *shapes);
  virtual bool canDoAction(std::vector<Shape *> *shapes);
};
