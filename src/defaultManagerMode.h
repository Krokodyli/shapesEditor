#pragma once

#include <chrono>

#include "managerMode.h"
#include "selectShapeCanvasAction.h"
#include "moveCanvasAction.h"
#include "deleteCanvasAction.h"
#include "newVertexCanvasAction.h"

using std::chrono::duration_cast;
using std::chrono::system_clock;
using std::chrono::milliseconds;

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

  int lastTimeClicked;

  int getTime();
  bool isSomethingSelected();
public:
  DefaultManagerMode();
  virtual void start(Canvas *canvas);
  virtual void update(Canvas *canvas, InputInfo *inputInfo);
  virtual void stop(Canvas *canvas);

  virtual void doAction(Canvas *canvas, int actionID);
  virtual bool canDoAction(Canvas *canvas, int actionID);

  static const int deleteActionID;
  static const int insertVertexActionID;
};
