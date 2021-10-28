#include "deleteCanvasAction.h"
#include "constraint.h"
#include "deleteAction.h"
#include "shapePart.h"
#include "shape.h"
#include <algorithm>

DeleteCanvasAction::DeleteCanvasAction(vector<Shape *> *_shapes,
                                       vector<ShapePart *> *_shapeParts,
                                       CanvasManagerState *_state)
  : shapes(_shapes), shapeParts(_shapeParts), state(_state) { }

void DeleteCanvasAction::doAction(std::vector<Shape *> *canvasShapes) {
  if(shapes->size() > 0)
    deleteShape((*shapes)[0], canvasShapes);
  else if(shapeParts->size() > 0)
    deleteShapePart((*shapeParts)[0], canvasShapes);
}

bool DeleteCanvasAction::canDoAction(std::vector<Shape *> *canvasShapes) {
  return shapes->size() > 0 || shapeParts->size() > 0;
}

void DeleteCanvasAction::deleteShape(Shape *shape,
                                     vector<Shape *> *canvasShapes) {

  DeleteAction deleteAction(state);
  shape->doAction(&deleteAction);
  if(deleteAction.isDeletingWholeShapeNeeded()) {
    deleteShapeFromCanvas(canvasShapes, shape);
    deleteShapeFromSelected(shape);
    delete shape;
  }
}

void DeleteCanvasAction::deleteShapePart(ShapePart *part,
                                         vector<Shape *> *canvasShapes) {
  Shape *parent = part->getParent();

  DeleteAction deleteAction(state, part);
  parent->doAction(&deleteAction);
  if (deleteAction.isDeletingWholeShapeNeeded())
    deleteShape(parent, canvasShapes);
  else
    deleteShapePartFromSelected(part);
}

void DeleteCanvasAction::deleteShapeFromCanvas(vector<Shape *> *canvasShapes,
                                               Shape *shape) {
  canvasShapes->erase(remove(canvasShapes->begin(), canvasShapes->end(),
                             shape), canvasShapes->end());
}

void DeleteCanvasAction::deleteShapeFromSelected(Shape *shape) {
  shapeParts->erase(remove_if(shapeParts->begin(), shapeParts->end(),
                              [&shape](ShapePart *part) {
                                return part->getParent()==shape;
                              }), shapeParts->end());
  shapes->erase(remove(shapes->begin(), shapes->end(), shape), shapes->end());
}

void DeleteCanvasAction::deleteShapePartFromSelected(ShapePart *shapePart) {
  shapeParts->erase(remove(shapeParts->begin(), shapeParts->end(), shapePart),
                    shapeParts->end());
}
