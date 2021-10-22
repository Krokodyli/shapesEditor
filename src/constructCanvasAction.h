#pragma once

#include <algorithm>

#include "canvasAction.h"
#include "constructionShape.h"
#include "point.h"
#include "polygon.h"

typedef function<ConstructionShape*(Canvas*)> createConstructionFunc;

class ConstructCanvasAction : public CanvasAction {
 private:
  enum class ConstructActionType {
    noAction,
    put,
    cleanUp,
    move
  };

  createConstructionFunc createShapeFunc;
  Canvas *canvas;

  ConstructActionType actionType;
  Point p;

  ConstructionShape *shape;

  void createIfNecessary(std::vector<Shape *> *shapes);
  void finishIfPossible(std::vector<Shape *> *shapes);
  void moveAction(std::vector<Shape*> *shapes);
  void putAction(std::vector<Shape *> *shapes);
  void cleanUpAction(std::vector<Shape *> *shapes);
public:
  ConstructCanvasAction(createConstructionFunc _createShapeFunc,
                        Canvas *_canvas);

  void moveConstructionPoint(Point newPos);
  void putConstructionPoint();
  void cleanUp();

  virtual void doAction(std::vector<Shape *> *shapes);
  virtual bool canDoAction(std::vector<Shape *> *shapes);
};
