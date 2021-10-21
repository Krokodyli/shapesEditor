#include "moveCanvasAction.h"
#include "moveAction.h"

void MoveCanvasAction::move(SelectCanvasAction *selectAction, Move _move) {
  shapes = selectAction->getSelectedShapes();
  shapeParts = selectAction->getSelectedShapeParts();
  moveValue = _move;
}

void MoveCanvasAction::doAction(std::vector<Shape *> *shapes) {
  MoveAction moveAction;
  moveAction.moveShape(moveValue);
  for(auto shape : this->shapes)
    shape->doAction(&moveAction);
  for (auto shapePart : shapeParts) {
    moveAction.moveShape(moveValue, shapePart);
    shapePart->getParent()->doAction(&moveAction);
  }
}

bool MoveCanvasAction::canDoAction(std::vector<Shape *> *shapes) {
  return false;
}
