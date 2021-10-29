#include "canvasDrawManager.h"

CanvasDrawManager::CanvasDrawManager() : antialiasing(false) { }

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
  if (a.x < b.x) {
    xi = 1;
    dx = b.x - a.x;
  }
  else
  {
    xi = -1;
    dx = a.x - b.x;
  }
  if (a.y < b.y) {
    yi = 1;
    dy = b.y - a.y;
  }
  else {
    yi = -1;
    dy = a.y - b.y;
  }
  putPixel(x, y);
  if (dx > dy)
  {
    ai = (dy - dx) * 2;
    bi = dy * 2;
    d = bi - dx;
    while (x != b.x) {
      if (d >= 0) {
        x += xi;
        y += yi;
        d += ai;
      }
      else {
        d += bi;
        x += xi;
      }
      putPixel(x, y);
    }
  }
  else {
    ai = ( dx - dy ) * 2;
    bi = dx * 2;
    d = bi - dy;
    while (y != b.y) {
      if (d >= 0) {
        x += xi;
        y += yi;
        d += ai;
      }
      else {
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
    drawCircleAntialiasing(c, r);
}

void CanvasDrawManager::drawCircleAntialiasing(Point a, int r) {
  int x = r;
  int y = 0;
  double T = 0;
  double D1;
  double D = 0;
  drawCirclePointsAntialiased(a.x, a.y, x, y, 1);
  while(x > y + 1) {
    y++;
    D1 = sqrt(r*r-y*y);
    D = ceil(D1) - D1;
    if(D < T)
      x--;
    drawCirclePointsAntialiased(a.x, a.y, x, y, 1-D);
    drawCirclePointsAntialiased(a.x, a.y, x - 1, y, D);
    T = D;
  }
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

void CanvasDrawManager::drawCirclePointsAntialiased(int xc, int yc, int x,
                                                    int y, double I) {
  putPixel(xc + x, yc + y, I);
  putPixel(xc - x, yc + y, I);
  putPixel(xc + x, yc - y, I);
  putPixel(xc - x, yc - y, I);

  putPixel(xc + y, yc + x, I);
  putPixel(xc - y, yc + x, I);
  putPixel(xc + y, yc - x, I);
  putPixel(xc - y, yc - x, I);
}

bool CanvasDrawManager::getAntialiasingState() {
  return antialiasing;
}

void CanvasDrawManager::setAntialiasingState(bool _antialiasing) {
  antialiasing = _antialiasing;
}
