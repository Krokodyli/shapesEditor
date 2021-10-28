#pragma once

#include <chrono>

#include "managerMode.h"
#include "selectShapeCanvasAction.h"
#include "moveCanvasAction.h"
#include "deleteCanvasAction.h"
#include "newVertexCanvasAction.h"

class DefaultManagerMode : public ManagerMode {
 private:
  vector<Shape*> selected;
  vector<ShapePart*> selectedParts;

  SelectCanvasAction selectAction;
  MoveCanvasAction moveAction;
  DeleteCanvasAction deleteAction;
  NewVertexCanvasAction newVertexAction;

  Point oldMousePos, mousePos;
  bool grabbed = false;

  bool isSomethingSelected();
public:
  DefaultManagerMode(CanvasManagerState *_state);

  virtual void start(Canvas *canvas);
  virtual void update(Canvas *canvas, InputInfo *inputInfo);
  virtual void stop(Canvas *canvas);

  virtual void doAction(Canvas *canvas, int actionID);
  virtual bool canDoAction(Canvas *canvas, int actionID);

  virtual void draw(DrawManager *drawManager, Canvas *canvas);

  static const int deleteActionID;
  static const int insertVertexActionID;
};
