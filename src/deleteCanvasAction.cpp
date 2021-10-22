#include "deleteCanvasAction.h"
#include "deleteAction.h"
#include "shapePart.h"
#include "shape.h"
#include <iostream>
#include <algorithm>

DeleteCanvasAction::DeleteCanvasAction(vector<Shape *> *_shapes,
                                       vector<ShapePart *> *_shapeParts)
  : shapes(_shapes), shapeParts(_shapeParts) { }

void DeleteCanvasAction::doAction(std::vector<Shape *> *canvasShapes) {
  if(shapes->size() > 0) {
    Shape *shape = (*shapes)[0];
    deleteShapeFromCanvas(canvasShapes, shape);
    deleteShapeFromSelected(shape);
    delete shape;
  }
  else if(shapeParts->size() > 0) {
    ShapePart *part = (*shapeParts)[0];
    Shape *parent = (*shapeParts)[0]->getParent();
    deleteShapePartFromSelected(part);

    DeleteAction deleteAction((*shapeParts)[0]);
    parent->doAction(&deleteAction);
    if(deleteAction.isDeletingWholeShapeNeeded()) {
      deleteShapeFromCanvas(canvasShapes, parent);
      deleteShapeFromSelected(parent);
      delete parent;
    }
  }
}

bool DeleteCanvasAction::canDoAction(std::vector<Shape *> *canvasShapes) {
  return shapes->size() > 0 || shapeParts->size() > 0;
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
