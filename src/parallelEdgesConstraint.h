#pragma once

#include <typeinfo>

#include "canvasManagerState.h"
#include "circleRing.h"
#include "constraint.h"
#include "shapePart.h"

class Edge;
class Vertex;
class ParallelEdgesConstraintCreator;

class ParallelEdgesConstraint : public Constraint {
private:
  Edge *a, *b;

  bool resolveWithVertex(Edge *edge, double expLen, Vertex *v,
                         CanvasManagerState *state, set<ShapePart *> *resolved);

  Point calculateRightPosition(Vertex *locked, Vertex *v, double expRatio);

  Edge *getEdgeFromVertex(ShapePart *part);

  Edge *getOtherEdge(Edge *e);
public:
  ParallelEdgesConstraint(Edge *_a, Edge *_b);
  virtual ~ParallelEdgesConstraint();

  virtual bool isConstraintBroken();

  virtual bool resolveConstraint(ShapePart *p, CanvasManagerState *state,
                                 set<ShapePart *> *resolved);

  virtual vector<ShapePart *> getAllConstrainted();

  virtual void draw(DrawManager *drawManager, ShapePart *part);
};

class ParallelEdgesConstraintCreator : public ConstraintCreator {
 private:
  virtual bool tryToResolve(ParallelEdgesConstraint* constraint,
                            CanvasManagerState *state, Edge *a, Edge *b);
 public:
  virtual bool canMakeConstraint(vector<ShapePart *> *parts,
                                 CanvasManagerState *state);

  virtual bool makeConstraint(vector<ShapePart *> *parts,
                              CanvasManagerState *state);
};
