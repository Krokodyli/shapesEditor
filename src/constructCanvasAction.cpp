#include "constructCanvasAction.h"
#include <iostream>

ConstructCanvasAction::ConstructCanvasAction(createConstructionFunc
                                             _createShapeFunc,
                                             Canvas *_canvas)
  : createShapeFunc(_createShapeFunc),
    canvas(_canvas),
    actionType(ConstructActionType::noAction),
    shape(nullptr) { }

void ConstructCanvasAction::moveConstructionPoint(Point newPos) {
  p = newPos;
  actionType = ConstructActionType::move;
}

void ConstructCanvasAction::putConstructionPoint() {
  actionType = ConstructActionType::put;
}

void ConstructCanvasAction::cleanUp() {
  actionType = ConstructActionType::cleanUp;
}

void ConstructCanvasAction::doAction(std::vector<Shape *> *shapes) {
  if(actionType == ConstructActionType::put)
    putAction(shapes);
  else if(actionType == ConstructActionType::move)
    moveAction(shapes);
  else if(actionType == ConstructActionType::cleanUp)
    cleanUpAction(shapes);
  actionType = ConstructActionType::noAction;
}

bool ConstructCanvasAction::canDoAction(std::vector<Shape *> *shapes) {
  return true;
}

void ConstructCanvasAction::createIfNecessary(std::vector<Shape *> *shapes) {
  if(shape == nullptr) {
    shape = createShapeFunc(canvas);
    shapes->push_back(shape);
    shape->start(p);
  }
}

void ConstructCanvasAction::finishIfPossible(std::vector<Shape *> *shapes) {
  if(shape != nullptr && shape->canFinishConstruction()) {
    shapes->erase(std::remove(shapes->begin(), shapes->end(), shape),
                  shapes->end());
    shapes->push_back(shape->finishShapeConstruction());
    delete shape;
    shape = nullptr;
  }
}

void ConstructCanvasAction::moveAction(std::vector<Shape *> *shapes) {
  createIfNecessary(shapes);
  shape->moveConstructionPoint(p);
}

void ConstructCanvasAction::putAction(std::vector<Shape *> *shapes) {
  createIfNecessary(shapes);
  shape->putConstructionPoint();
  finishIfPossible(shapes);
  createIfNecessary(shapes);
}

void ConstructCanvasAction::cleanUpAction(std::vector<Shape *> *shapes) {
  if (shape != nullptr) {
    shapes->erase(std::remove(shapes->begin(), shapes->end(), shape),
                  shapes->end());
    delete shape;
    shape = nullptr;
  }
}
