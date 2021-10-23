#include "newVertexCanvasAction.h"
#include "shapePart.h"
#include "shape.h"
#include "newVertexAction.h"
#include <iostream>

NewVertexCanvasAction::NewVertexCanvasAction(vector<Shape *> *_shapes,
                                             vector<ShapePart *> *_shapeParts)
    : shapes(_shapes), shapeParts(_shapeParts) {}

void NewVertexCanvasAction::doAction(std::vector<Shape *> *canvasShapes) {
  if(shapeParts->size() > 0 && shapes->size() == 0) {
    auto shapePart = (*shapeParts)[0];
    NewVertexAction newVertexAction(shapePart);
    shapePart->getParent()->doAction(&newVertexAction);
  }
}

bool NewVertexCanvasAction::canDoAction(std::vector<Shape *> *canvasShapes) {
  if (shapeParts->size() > 0 && shapes->size() == 0) {
    auto shapePart = (*shapeParts)[0];
    NewVertexAction newVertexAction(shapePart);
    return shapePart->getParent()->canDoAction(&newVertexAction);
  }
  else {
    return false;
  }
}
