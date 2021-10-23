#pragma once

#include "canvasAction.h"
#include "constraint.h"

class ShapePart;

class DeleteCanvasAction : public CanvasAction {
 private:
  vector<Shape*> *shapes;
  vector<ShapePart*> *shapeParts;
  CanvasManagerState *state;

  void deleteShape(Shape *shape, vector<Shape*> *canvasShapes);
  void deleteShapePart(ShapePart *part, vector<Shape *> *canvasShapes);

  void deleteShapeFromCanvas(vector<Shape*> *canvasShapes, Shape* shape);

  void deleteShapeFromSelected(Shape *shape);
  void deleteShapePartFromSelected(ShapePart *shapePart);
public:
  DeleteCanvasAction(vector<Shape*> *_shapes,
                     vector<ShapePart*> *_shapeParts,
                     CanvasManagerState *_state);
  virtual void doAction(std::vector<Shape *> *canvasShapes);
  virtual bool canDoAction(std::vector<Shape *> *canvasShapes);
};
