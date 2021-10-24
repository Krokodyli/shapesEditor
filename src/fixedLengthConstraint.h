#pragma once

#include <typeinfo>

#include "canvasManagerState.h"
#include "circleRing.h"
#include "constraint.h"

class Edge;
class Vertex;

class FixedLengthConstraint : public Constraint {
private:
  Edge *edge;
  double length;

  Vertex *getVertex(ShapePart *part);
  Point calculateRightPosition(Vertex *locked, Vertex *v);
public:
  FixedLengthConstraint(Edge *_edge);
  virtual ~FixedLengthConstraint();

  virtual bool isConstraintBroken();
  virtual bool
  resolveConstraint(ShapePart *p, CanvasManagerState *state,
                    set<ShapePart *> *resolved);
  virtual vector<ShapePart *> getAllConstrainted();
  virtual void draw(DrawManager *drawManager, ShapePart *part);
};

class FixedLengthConstraintCreator : public ConstraintCreator {
public:
  virtual bool canMakeConstraint(vector<ShapePart *> *parts,
                                 CanvasManagerState *state);
  virtual bool makeConstraint(vector<ShapePart *> *parts,
                              CanvasManagerState *state);
};
