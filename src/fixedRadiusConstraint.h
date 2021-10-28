#pragma once

#include <typeinfo>

#include "canvasManagerState.h"
#include "circleRing.h"
#include "constraint.h"
#include "shapePart.h"

class FixedRadiusConstraint : public Constraint {
private:
  CircleRing *ring;
  int fixedRadius;
public:
  FixedRadiusConstraint(CircleRing *_ring);
  virtual ~FixedRadiusConstraint();

  virtual bool isConstraintBroken();

  virtual bool resolveConstraint(ShapePart *p, CanvasManagerState *state,
                                 set<ShapePart *> *resolved);

  virtual vector<ShapePart *> getAllConstrainted();

  virtual void draw(DrawManager *drawManager, ShapePart *part);
};

class FixedRadiusConstraintCreator : public ConstraintCreator {
public:
  virtual bool canMakeConstraint(vector<ShapePart *> *parts,
                                 CanvasManagerState *state);

  virtual bool makeConstraint(vector<ShapePart *> *parts,
                              CanvasManagerState *state);
};
