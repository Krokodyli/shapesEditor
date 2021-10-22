#include "moveCanvasAction.h"
#include "moveAction.h"

MoveCanvasAction::MoveCanvasAction(vector<Shape *> *_shapes,
                                   vector<ShapePart *> *_shapeParts)
  : shapes(_shapes), shapeParts(_shapeParts) { }

void MoveCanvasAction::move(Move _move) {
  moveValue = _move;
}

void MoveCanvasAction::doAction(std::vector<Shape *> *_shapes) {
  MoveAction moveAction;
  moveAction.moveShape(moveValue);
  for(auto shape : *shapes)
    shape->doAction(&moveAction);
  for (auto shapePart : *shapeParts) {
    moveAction.moveShape(moveValue, shapePart);
    shapePart->getParent()->doAction(&moveAction);
  }
}

bool MoveCanvasAction::canDoAction(std::vector<Shape *> *_shapes) {
  return false;
}
