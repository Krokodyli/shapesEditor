#pragma once

#include "color.h"
#include "drawManager.h"

double fpart(double a);
double rfpart(double a);

class CanvasDrawManager {
 protected:
  bool antialiasing;

  virtual void drawCirclePoints(int xc, int yc, int x, int y);
  virtual void putPixel(int x, int y) = 0;
  virtual void putPixel(int x, int y, double brightness) = 0;
  virtual void prepareColor(Color c) = 0;

 public:
  CanvasDrawManager();
  virtual ~CanvasDrawManager();

  virtual void drawLine(Point a, Point b, Color color);
  virtual void drawCircle(Point c, int r, Color color);

  virtual void drawLineAliasing(Point a, Point b);
  virtual void drawCircleAliasing(Point c, int r);

  virtual void drawLineAntialiasing(Point a, Point b);
  virtual void drawCircleAntialiasing(Point a, int r);

  virtual void display(DrawManager *drawManager) = 0;

  virtual bool getAntialiasingState();
  virtual void setAntialiasingState(bool _antialiasing);
};
