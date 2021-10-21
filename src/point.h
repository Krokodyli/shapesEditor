#pragma once

#include <math.h>

class Point {
 public:
  int x, y;

  Point();
  Point(int _x, int _y);

  Point operator+(const Point &r);
  Point operator-(const Point &r);
  Point operator*(const int &r);
  Point operator*(const double &r);
  Point operator/(const int &r);
  Point operator/(const double &r);

  double dis(const Point &r);
  int dissq(const Point &r);
};
