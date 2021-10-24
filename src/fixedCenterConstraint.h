#pragma once

#include <typeinfo>

#include "canvasManagerState.h"
#include "constraint.h"
#include "circleRing.h"

class Circle;

class FixedCenterConstraint : public Constraint {
 private:
  CircleCenter *center;
  Point fixedPos;

  bool isCircleOutsideCanvas(Circle *circle);
 public:
  FixedCenterConstraint(CircleCenter *_center);
  virtual ~FixedCenterConstraint();

  virtual bool isConstraintBroken();
  virtual bool resolveConstraint(ShapePart *p, CanvasManagerState *state,
                                 set<ShapePart *> *resolved);
  virtual vector<ShapePart *> getAllConstrainted();
  virtual void draw(DrawManager *drawManager, ShapePart *part);
};

class FixedCenterConstraintCreator : public ConstraintCreator {
public:
  virtual bool canMakeConstraint(vector<ShapePart *> *parts,
                                 CanvasManagerState *state);
  virtual bool makeConstraint(vector<ShapePart *> *parts,
                              CanvasManagerState *state);
};
