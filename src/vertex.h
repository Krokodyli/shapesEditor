#pragma once

#include "shapePart.h"

class Edge;

class Vertex : public ShapePart {
 private:
   Point pos;
   Edge *a, *b;
 public:
  Vertex(Point _pos, Shape *_parent, Edge *_a = nullptr, Edge *_b = nullptr);
  virtual ~Vertex();

  void setPos(Point _pos);
  Point getPos();

  void setA(Edge *_a);
  void setB(Edge *_b);
  Edge *getA();
  Edge *getB();

  Edge *getOtherEdge(Edge *_a);

  virtual bool isUnderPoint(Point p);

  virtual void drawOnCanvas(CanvasDrawManager *drawManager);
  virtual void draw(DrawManager *drawManager);
};
