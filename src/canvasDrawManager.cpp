#include "canvasDrawManager.h"
#include <iostream>

CanvasDrawManager::~CanvasDrawManager() { }

double fpart(double a) {
  return a - floor(a);
}
double rfpart(double a) {
  return 1 - fpart(a);
}

void CanvasDrawManager::drawLineAntialiasing(Point a, Point b) {
  if(a.y >= b.y) std::swap(a, b);
  double y0 = a.y, x0 = a.x;
  double y1 = b.y, x1 = b.x;
  bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);

  if(steep) {
    std::swap(x0, y0);
    std::swap(x1, y1);
  }
  else if(x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  double dx = x1 - x0;
  double dy = y1 - y0;
  double gradient = dy / dx;

  if(dx == 0.0) {
    gradient = 1.0;
  }

  double xend = round(x0);
  double yend = y0 + gradient * (xend - x0);
  double xgap = rfpart(x0 + 0.5);
  double xpxl1 = xend;
  double ypxl1 = floor(yend);
  if(steep) {
    putPixel(ypxl1, xpxl1, rfpart(yend) * xgap);
    putPixel(ypxl1+1, xpxl1, rfpart(yend) * xgap);
  }
  else {
    putPixel(xpxl1, ypxl1  , rfpart(yend) * xgap);
    putPixel(xpxl1, ypxl1+1,  fpart(yend) * xgap);
  }
  double intery = yend + gradient;

  xend = round(x1);
  yend = y1 + gradient * (xend - x1);
  xgap = fpart(x1 + 0.5);
  double xpxl2 = xend;
  double ypxl2 = floor(yend);
  if(steep) {
    putPixel(ypxl2  , xpxl2, rfpart(yend) * xgap);
    putPixel(ypxl2+1, xpxl2,  fpart(yend) * xgap);
  }
  else {
    putPixel(xpxl2, ypxl2,  rfpart(yend) * xgap);
    putPixel(xpxl2, ypxl2+1, fpart(yend) * xgap);
  }

  if(steep) {
    for(double x = xpxl1 + 1; x <= xpxl2 - 1; x++) {
      putPixel(floor(intery), x, rfpart(intery));
      putPixel(floor(intery)+1, x, fpart(intery));
      intery = intery + gradient;
    }
  }
  else {
    for(double x = xpxl1 + 1; x <= xpxl2 - 1; x++) {
      putPixel(x, floor(intery), rfpart(intery));
      putPixel(x, floor(intery)+1, fpart(intery));
      intery = intery + gradient;
    }
  }
}
/*
void CanvasDrawManager::drawLineAntialiasing2(Point a, Point b) {
  auto ipart = [](double x) -> int {return int(std::floor(x));};
  auto round = [](double x) -> double {return std::round(x);};
  auto fpart = [](double x) -> double {return x - std::floor(x);};
  auto rfpart = [=](double x) -> double {return 1 - fpart(x);};
  auto plot = [=](int x, int y, double b) -> void { putPixel(x, y, b); };
  double x0 = a.x, y0 = a.y;
  double x1 = b.x, y1 = b.y;

  const bool steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    std::swap(x0,y0);
    std::swap(x1,y1);
  }
  if (x0 > x1) {
    std::swap(x0,x1);
    std::swap(y0,y1);
  }

  const double dx = x1 - x0;
  const double dy = y1 - y0;
  const double gradient = (dx == 0) ? 1 : dy/dx;

  int xpx11;
  double intery;
  {
    const double xend = round(x0);
    const double yend = y0 + gradient * (xend - x0);
    const double xgap = rfpart(x0 + 0.5);
    xpx11 = int(xend);
    const int ypx11 = ipart(yend);
    if (steep) {
      plot(ypx11,     xpx11, rfpart(yend) * xgap);
      plot(ypx11 + 1, xpx11,  fpart(yend) * xgap);
    } else {
      plot(xpx11, ypx11,    rfpart(yend) * xgap);
      plot(xpx11, ypx11 + 1, fpart(yend) * xgap);
    }
    intery = yend + gradient;
  }

  int xpx12;
  {
    const double xend = round(x1);
    const double yend = y1 + gradient * (xend - x1);
    const double xgap = rfpart(x1 + 0.5);
    xpx12 = int(xend);
    const int ypx12 = ipart(yend);
    if (steep) {
      plot(ypx12,     xpx12, rfpart(yend) * xgap);
      plot(ypx12 + 1, xpx12,  fpart(yend) * xgap);
    }
    else {
      plot(xpx12, ypx12,    rfpart(yend) * xgap);
      plot(xpx12, ypx12 + 1, fpart(yend) * xgap);
    }
  }

  if (steep) {
    for (int x = xpx11 + 1; x < xpx12; x++) {
      plot(ipart(intery),     x, rfpart(intery));
        plot(ipart(intery) + 1, x,  fpart(intery));
        intery += gradient;
    }
  }
  else {
    for (int x = xpx11 + 1; x < xpx12; x++) {
      plot(x, ipart(intery),     rfpart(intery));
      plot(x, ipart(intery) + 1,  fpart(intery));
      intery += gradient;
    }
  }
}
*/
void CanvasDrawManager::drawLine(Point a, Point b, Color color) {
  prepareColor(color);
  if(antialiasing)
    drawLineAntialiasing(a, b);
  else
    drawLineAliasing(a, b);
}

void CanvasDrawManager::drawLineAliasing(Point a, Point b) {
  int d, dx, dy, ai, bi, xi, yi;
  int x = a.x, y = a.y;
  if (a.x < b.x)
  {
      xi = 1;
      dx = b.x - a.x;
  }
  else
  {
      xi = -1;
      dx = a.x - b.x;
  }
  if (a.y < b.y)
  {
      yi = 1;
      dy = b.y - a.y;
  }
  else
  {
      yi = -1;
      dy = a.y - b.y;
  }
  putPixel(x, y);
  if (dx > dy)
  {
      ai = (dy - dx) * 2;
      bi = dy * 2;
      d = bi - dx;
      while (x != b.x)
      {
          if (d >= 0)
          {
              x += xi;
              y += yi;
              d += ai;
          }
          else
          {
              d += bi;
              x += xi;
          }
          putPixel(x, y);
      }
  }
  else
  {
      ai = ( dx - dy ) * 2;
      bi = dx * 2;
      d = bi - dy;
      while (y != b.y)
      {
          if (d >= 0)
          {
              x += xi;
              y += yi;
              d += ai;
          }
          else
          {
              d += bi;
              y += yi;
          }
          putPixel(x, y);
      }
  }
}

void CanvasDrawManager::drawCircle(Point c, int r, Color color) {
  if (r == 0)
    return;
  prepareColor(color);
  if(!antialiasing)
    drawCircleAliasing(c, r);
  else
    drawCircleAliasing(c, r); // nie działa :(((((
}

void CanvasDrawManager::drawCircleAntialiasing(Point a, int r) {
}

void CanvasDrawManager::drawCircleAliasing(Point c,  int r){
  int x = 0, y = r;
  int param = 3 - 2 * r;
  drawCirclePoints(c.x, c.y, x, y);
  while(y >= x) {
    x++;
    if(param > 0) {
      y--;
      param = param + 4 * (x - y) + 10;
    }
    else {
      param = param + 4 * x + 6;
    }
    drawCirclePoints(c.x, c.y, x, y);
  }
}

void CanvasDrawManager::drawCirclePoints(int xc, int yc, int x, int y) {
  putPixel(xc + x, yc + y);
  putPixel(xc - x, yc + y);
  putPixel(xc + x, yc - y);
  putPixel(xc - x, yc - y);

  putPixel(xc + y, yc + x);
  putPixel(xc - y, yc + x);
  putPixel(xc + y, yc - x);
  putPixel(xc - y, yc - x);
}

bool CanvasDrawManager::getAntialiasingState() {
  return antialiasing;
}

void CanvasDrawManager::setAntialiasingState(bool _antialiasing) {
  antialiasing = _antialiasing;
}
