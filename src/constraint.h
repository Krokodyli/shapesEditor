#pragma once

#include <vector>
#include <set>

#include "shapePart.h"

using std::set;
using std::vector;

class CanvasManagerState;

class Constraint {
 protected:
  Color color;
 public:
  Constraint();
  virtual ~Constraint();
  virtual bool isConstraintBroken() = 0;
  virtual bool resolveConstraint(ShapePart *p, CanvasManagerState *state,
                                 set<ShapePart*> *resolved) = 0;
  virtual vector<ShapePart *> getAllConstrainted() = 0;
  virtual void draw(DrawManager *drawManager, ShapePart *part) = 0;
};

class ConstraintCreator {
 public:
  virtual ~ConstraintCreator();
  virtual bool canMakeConstraint(vector<ShapePart*> *parts,
                                 CanvasManagerState *state) = 0;
  virtual bool makeConstraint(vector<ShapePart *> *parts,
                              CanvasManagerState *state) = 0;
};
