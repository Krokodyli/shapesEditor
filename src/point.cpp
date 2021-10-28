#include "point.h"
#include <algorithm>

Point::Point(int _x, int _y) : x(_x), y(_y) {}

Point::Point() : x(0), y(0) {}

Point Point::operator+(const Point &r) {
  return Point(x + r.x, y + r.y);
}

Point Point::operator-(const Point &r) {
  return Point(x - r.x, y - r.y);
}

Point Point::operator*(const int &r) {
  return Point(x * r, y * r);
}

Point Point::operator*(const double &r) {
  return Point(x * r, y * r);
}

Point Point::operator/(const int &r) {
  return Point(x / r, y / r);
}

Point Point::operator/(const double &r) {
  return Point(x / r, y / r);
}

bool Point::operator==(const Point &r) {
  return x == r.x && y == r.y;
}

bool Point::operator!=(const Point &r) {
  return !operator==(r);
}

double Point::dis(const Point &r) {
  return sqrt(dissq(r));
}

int Point::dissq(const Point &r) {
  return (x-r.x)*(x-r.x) + (y-r.y)*(y-r.y);
}

bool Point::insideRec(int _x, int _y, int width, int height) {
  return x >= _x && x <= _x + width && y >= _y && y <= _y + height;
}

Point Point::fix2Rec(Point min, Point max) {
  Point p(x, y);

  p.x = std::max(p.x, min.x);
  p.x = std::min(p.x, max.x - 1);

  p.y = std::max(p.y, min.y);
  p.y = std::min(p.y, max.y - 1);

  return p;
}
