#pragma once

#include <typeinfo>

#include "canvasManagerState.h"
#include "circleCenter.h"
#include "circleRing.h"
#include "constraint.h"
#include "shapePart.h"
#include "circle.h"
#include "edge.h"
#include "vertex.h"


class TangentConstraint : public Constraint {
private:
  Edge *a;

  Circle *c;
  CircleCenter *p;
  CircleRing *r;

  bool resolveForEdge(CanvasManagerState *state, set<ShapePart*> *resolved);
  bool resolveForCircle(CanvasManagerState *state, set<ShapePart *> *resolved);
  std::pair<Point, Point> getPerpendicularPoint(Point m, Point b, double len);
public:
  TangentConstraint(Edge *_a, Circle *_c);
  virtual ~TangentConstraint();

  virtual bool isConstraintBroken();
  virtual bool
  resolveConstraint(ShapePart *part, CanvasManagerState *state,
                    set<ShapePart *> *resolved);
  virtual vector<ShapePart *> getAllConstrainted();
  virtual void draw(DrawManager *drawManager, ShapePart *part);
};

class TangentConstraintCreator : public ConstraintCreator {
 private:
  virtual bool tryToResolve(TangentConstraint* constraint, CanvasManagerState *state,
                            Edge *a, Circle *c);

  virtual Edge *getEdge(vector<ShapePart*> *parts);
  virtual CircleRing *getRing(vector<ShapePart *> *parts);
  virtual CircleCenter *getCenter(vector<ShapePart *> *parts);
public:
  virtual bool canMakeConstraint(vector<ShapePart *> *parts,
                                 CanvasManagerState *state);
  virtual bool makeConstraint(vector<ShapePart *> *parts,
                              CanvasManagerState *state);
};
