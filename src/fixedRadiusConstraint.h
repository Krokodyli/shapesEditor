#pragma once

#include <typeinfo>

#include "circleRing.h"
#include "constraint.h"

class FixedRadiusConstraint : public Constraint {
private:
  CircleRing *ring;
  int fixedRadius;

public:
  FixedRadiusConstraint(CircleRing *_ring);
  virtual ~FixedRadiusConstraint();

  virtual bool isConstraintBroken();
  virtual bool resolveConstraint(ShapePart *p,
                    set<ShapePart *> resolved = set<ShapePart *>());
  virtual vector<ShapePart *> getAllConstrainted();
  virtual void draw(DrawManager *drawManager);
};

class FixedRadiusConstraintCreator : public ConstraintCreator {
public:
  virtual bool canMakeConstraint(vector<ShapePart *> *parts,
                                 CanvasManagerState *state);
  virtual bool makeConstraint(vector<ShapePart *> *parts,
                              CanvasManagerState *state);
};
