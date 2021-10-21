#pragma once

#include "shapePart.h"

class Vertex;

class Edge : public ShapePart {
 private:
  Vertex *a, *b;
 public:
  Edge(Shape *_parent, Vertex *_a = nullptr, Vertex *_b = nullptr);
  virtual ~Edge();

  void setA(Vertex *_a);
  void setB(Vertex *_b);
  Vertex *getA();
  Vertex *getB();

  Vertex *getOtherVertex(Vertex *_a);

  virtual bool isUnderPoint(Point p);

  virtual void drawOnCanvas(CanvasDrawManager *drawManager);
  virtual void draw(DrawManager *drawManager);
};
