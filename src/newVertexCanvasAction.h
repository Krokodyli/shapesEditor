#pragma once

#include "canvasAction.h"
#include "canvasManagerState.h"

class ShapePart;

class NewVertexCanvasAction : public CanvasAction {
private:
  vector<Shape *> *shapes;
  vector<ShapePart *> *shapeParts;

  CanvasManagerState *state;
public:
  NewVertexCanvasAction(vector<Shape *> *_shapes,
                        vector<ShapePart *> *_shapeParts,
                        CanvasManagerState *_state);

  virtual void doAction(std::vector<Shape *> *canvasShapes);
  virtual bool canDoAction(std::vector<Shape *> *canvasShapes);
};
