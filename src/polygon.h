#pragma once

#include <vector>
#include <functional>

#include "shape.h"
#include "vertex.h"
#include "edge.h"

using std::vector;
using std::function;

class Polygon : public Shape {
 private:
  Vertex *head;

  void createPolygonFromPoints(vector<Point> points);
  void deletePolygon();
public:
  Polygon(vector<Point> points, Canvas *_canvas);
  virtual ~Polygon();

  Vertex *getHead();
  void setHead(Vertex *v);

  void map2Vertices(function<void(Vertex *)> f);
  void map2Edges(function<void(Edge *)> f);

  virtual void doAction(ShapeAction *shapeAction);
  virtual bool canDoAction(ShapeAction *shapeAction);

  virtual void drawOnCanvas(CanvasDrawManager *drawManager);
  virtual void draw(DrawManager *drawManager);
};
