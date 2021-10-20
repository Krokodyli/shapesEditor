#pragma once

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
};
