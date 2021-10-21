#pragma once

#include <vector>
#include <functional>

#include "shape.h"

using std::vector;
using std::function;

class Vertex;
class Edge;

class Polygon : public Shape {
 private:
  Vertex *head;

  void createPolygonFromPoints(vector<Point> points);
  void deletePolygon();
public:
  Polygon(vector<Point> points, Canvas *_canvas);
  virtual ~Polygon();

  void map2Vertices(function<void(Vertex *)> f);
  void map2Edges(function<void(Edge *)> f);

  virtual void doAction(ShapeAction *shapeAction);
  virtual bool canDoAction(ShapeAction *shapeAction);

  virtual void drawOnCanvas(CanvasDrawManager *drawManager);
  virtual void draw(DrawManager *drawManager);
};
