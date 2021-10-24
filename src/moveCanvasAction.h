#pragma once

#include <vector>

#include "constraint.h"
#include "move.h"
#include "canvasAction.h"
#include "selectShapeCanvasAction.h"

using std::vector;

class Shape;

class MoveCanvasAction : public CanvasAction {
 private:
  Move moveValue;
  vector<Shape*> *shapes;
  vector<ShapePart*> *shapeParts;
  CanvasManagerState *state;

  vector<Move> splitMove();
public:
  MoveCanvasAction(vector<Shape*> *_shapes, vector<ShapePart*> *_shapeParts,
                   CanvasManagerState *_state);

  void move(Move _move);

  virtual void doAction(std::vector<Shape *> *_shapes);
  virtual bool canDoAction(std::vector<Shape *> *_shapes);
};
