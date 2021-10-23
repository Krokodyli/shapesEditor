#include "polygon.h"
#include "shapeAction.h"
#include "vertex.h"
#include "edge.h"
#include "canvas.h"

Polygon::Polygon(vector<Point> points, Canvas *_canvas) : Shape(_canvas) {
  head = nullptr;
  createPolygonFromPoints(points);
}

Polygon::~Polygon() {
  deletePolygon();
}

Vertex *Polygon::getHead() {
  return head;
}

void Polygon::setHead(Vertex *v) {
  head = v;
}

void Polygon::map2Vertices(function<void(Vertex *)> f) {
  Vertex *it = head;
  f(it);
  it = it->getB()->getB();
  while (it != head) {
    f(it);
    it = it->getB()->getB();
  }
}

void Polygon::map2Edges(function<void(Edge *)> f) {
  Edge *it = head->getB();
  f(it);
  it = it->getB()->getB();
  while (it->getA() != head) {
    f(it);
    it = it->getB()->getB();
  }
}

void Polygon::doAction(ShapeAction *shapeAction) {
  shapeAction->doAction(this);
}

bool Polygon::canDoAction(ShapeAction *shapeAction) {
  return shapeAction->canDoAction(this);
}

void Polygon::drawOnCanvas(CanvasDrawManager *drawManager) {
  map2Edges([drawManager](Edge *e) {
    e->drawOnCanvas(drawManager);
  });
}

void Polygon::draw(DrawManager *drawManager) {
  map2Vertices([drawManager](Vertex *v) {
    v->draw(drawManager);
  });
}

void Polygon::createPolygonFromPoints(vector<Point> points) {
  if(head != nullptr) deletePolygon();
  int n = points.size();
  vector<Vertex*> vertices;
  vector<Edge *> edges;
  for(auto p : points)
    vertices.push_back(new Vertex(p, this));

  for(int i = 0; i < n; i++)
    edges.push_back(new Edge(this, vertices[i], vertices[(i+1)%n]));

  for(int i = 0; i < n; i++) {
    vertices[i]->setA(edges[(i+n-1)%n]);
    vertices[i]->setB(edges[i]);
  }

  head = vertices[0];
}

void Polygon::deletePolygon() {
  if(head == nullptr) return;
  Vertex *firstVertex = head;
  Vertex *it = head->getB()->getB();
  while(it != firstVertex) {
    Vertex *next = it->getB()->getB();
    delete it->getB();
    delete it;
    it = next;
  }
  delete firstVertex->getB();
  delete firstVertex;
  head = nullptr;
}

bool Polygon::isShapeOutsideCanvas() {
  bool isOutside = false;
  map2Vertices([this, &isOutside](Vertex *v) {
    if(!v->getPos().insideRec(0, 0, canvas->getPos().x, canvas->getPos().y))
      isOutside = true;
  });
  return isOutside;
}
