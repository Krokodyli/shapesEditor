#pragma once

#include "canvasAction.h"

class ShapePart;

class NewVertexCanvasAction : public CanvasAction {
private:
  vector<Shape *> *shapes;
  vector<ShapePart *> *shapeParts;

public:
  NewVertexCanvasAction(vector<Shape *> *_shapes,
                        vector<ShapePart *> *_shapeParts);
  virtual void doAction(std::vector<Shape *> *canvasShapes);
  virtual bool canDoAction(std::vector<Shape *> *canvasShapes);
};
