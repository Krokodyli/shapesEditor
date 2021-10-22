#pragma once

#include "canvasAction.h"

class ShapePart;

class DeleteCanvasAction : public CanvasAction {
 private:
  vector<Shape*> *shapes;
  vector<ShapePart*> *shapeParts;

  void deleteShapeFromCanvas(vector<Shape*> *canvasShapes, Shape* shape);
  void deleteShapeFromSelected(Shape *shape);
  void deleteShapePartFromSelected(ShapePart *shapePart);
public:
  DeleteCanvasAction(vector<Shape*> *_shapes,
                     vector<ShapePart*> *_shapeParts);
  virtual void doAction(std::vector<Shape *> *canvasShapes);
  virtual bool canDoAction(std::vector<Shape *> *canvasShapes);
};
