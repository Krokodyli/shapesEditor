#pragma once

#include "drawManager.h"
#include "canvas.h"
#include "canvasManager.h"
#include "toolbar.h"

class App {
 protected:
  Point size;
  Point canvasPos;
  Point canvasSize;

  DrawManager *drawManager;
  CanvasDrawManager *canvasDrawManager;
  InputInfo *inputInfo;

  Canvas *canvas;
  CanvasManager *canvasManager;
  Toolbar *toolbar;

  bool isRunning;

  virtual void initialSetup();
  virtual void setup();
  virtual void draw();
  virtual void update();
  virtual void handleEvents();
public:
  App(Point _size);
  virtual ~App() = 0;
  virtual void execute();
};
