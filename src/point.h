#pragma once

#include <math.h>

struct Point {
  int x, y;

  Point();
  Point(int _x, int _y);

  Point operator+(const Point &r);
  Point operator-(const Point &r);
  Point operator*(const int &r);
  Point operator*(const double &r);
  Point operator/(const int &r);
  Point operator/(const double &r);
  bool operator==(const Point &r);
  bool operator!=(const Point &r);

  double dis(const Point &r);
  int dissq(const Point &r);

  bool insideRec(int _x, int _y, int width, int height);
  Point fix2Rec(Point min, Point max);
};
