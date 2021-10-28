#include "newVertexCanvasAction.h"
#include "canvasManagerState.h"
#include "shapePart.h"
#include "shape.h"
#include "newVertexAction.h"

NewVertexCanvasAction::NewVertexCanvasAction(vector<Shape *> *_shapes,
                                             vector<ShapePart *> *_shapeParts,
                                             CanvasManagerState *_state)
  : shapes(_shapes), shapeParts(_shapeParts), state(_state) { }

void NewVertexCanvasAction::doAction(std::vector<Shape *> *canvasShapes) {
  if(shapeParts->size() > 0 && shapes->size() == 0) {
    auto shapePart = (*shapeParts)[0];
    NewVertexAction newVertexAction(shapePart, state);
    shapePart->getParent()->doAction(&newVertexAction);
  }
}

bool NewVertexCanvasAction::canDoAction(std::vector<Shape *> *canvasShapes) {
  if(shapeParts->size() == 0 || shapes->size() != 0)
    return false;

  auto shapePart = (*shapeParts)[0];
  NewVertexAction newVertexAction(shapePart, state);
  return shapePart->getParent()->canDoAction(&newVertexAction);
}
