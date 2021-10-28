#pragma once

#include <unordered_map>

#include "drawManager.h"
#include "managerMode.h"
#include "selectShapeCanvasAction.h"

class ConstraintsManagerMode : public ManagerMode {
 private:
  vector<Shape*> selected;
  vector<ShapePart*> selectedParts;

  SelectCanvasAction selectAction;

  unordered_map<int, ConstraintCreator*> constraintCreators;

  void setupConstraintCreators();
  void deleteConstraint();
  bool canDeleteConstraint();
 public:
  ConstraintsManagerMode(CanvasManagerState *_state);
  virtual ~ConstraintsManagerMode();

  virtual void start(Canvas *canvas);
  virtual void update(Canvas *canvas, InputInfo *inputInfo);
  virtual void stop(Canvas *canvas);

  virtual void doAction(Canvas *canvas, int actionID);
  virtual bool canDoAction(Canvas *canvas, int actionID);

  virtual void draw(DrawManager *drawManager, Canvas *canvas);

  static const int makeFixedRadiusConstraint;
  static const int makeFixedCenterConstraint;
  static const int makeFixedLengthConstraint;
  static const int makeEqualEdgesConstraint;
  static const int makeParallelEdgesConstraint;
  static const int makeTangentConstraint;
  static const int deleteConstraints;
};
