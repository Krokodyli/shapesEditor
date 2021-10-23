#include "moveCanvasAction.h"
#include "constraint.h"
#include "moveAction.h"

MoveCanvasAction::MoveCanvasAction(vector<Shape *> *_shapes,
                                   vector<ShapePart *> *_shapeParts,
                                   CanvasManagerState *_state)
  : shapes(_shapes), shapeParts(_shapeParts), state(_state) { }

void MoveCanvasAction::move(Move _move) {
  moveValue = _move;
}

void MoveCanvasAction::doAction(std::vector<Shape *> *_shapes) {
  MoveAction moveAction;
  moveAction.moveShape(moveValue, state);
  for(auto shape : *shapes)
    shape->doAction(&moveAction);
  for (auto shapePart : *shapeParts) {
    moveAction.moveShape(moveValue, state, shapePart);
    shapePart->getParent()->doAction(&moveAction);
  }
}

bool MoveCanvasAction::canDoAction(std::vector<Shape *> *_shapes) {
  return false;
}
