#include "point.h"

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
