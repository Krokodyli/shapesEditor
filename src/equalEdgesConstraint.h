#pragma once

#include <typeinfo>

#include "canvasManagerState.h"
#include "circleRing.h"
#include "constraint.h"
#include "shapePart.h"

class Edge;
class Vertex;
class EqualEdgesConstraintCreator;

class EqualEdgesConstraint : public Constraint {
private:
  Edge *a, *b;

  Edge *getEdgeFromVertex(ShapePart *part);
  Edge *getOtherEdge(Edge *e);

  bool resolveWithVertex(Edge *edge, double expLen, Vertex *v,
                         CanvasManagerState *state,
                         set<ShapePart*> *resolved);
  Point calculateRightPosition(Vertex *locked, Vertex *v, double expLen);
public:
  EqualEdgesConstraint(Edge *_a, Edge *_b);
  virtual ~EqualEdgesConstraint();

  virtual bool isConstraintBroken();
  virtual bool
  resolveConstraint(ShapePart *p, CanvasManagerState *state,
                    set<ShapePart *> *resolved);
  virtual vector<ShapePart *> getAllConstrainted();
  virtual void draw(DrawManager *drawManager, ShapePart *part);
};

class EqualEdgesConstraintCreator : public ConstraintCreator {
 private:
  virtual bool tryToResolve(EqualEdgesConstraint* constraint, CanvasManagerState *state,
                            Edge *a, Edge *b);
 public:
  virtual bool canMakeConstraint(vector<ShapePart *> *parts,
                                 CanvasManagerState *state);
  virtual bool makeConstraint(vector<ShapePart *> *parts,
                              CanvasManagerState *state);
};
