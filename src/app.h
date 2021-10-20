#pragma once

#include "drawManager.h"
#include "canvas.h"
#include "canvasManager.h"
#include "toolbar.h"

class App {
 protected:
  DrawManager *drawManager;
  InputInfo *inputInfo;

  Canvas *canvas;
  CanvasManager *canvasManager;
  Toolbar *toolbar;

  bool isRunning;

  virtual void setup();
  virtual void draw();
  virtual void update();
  virtual void handleEvents();
public:
  virtual ~App() = 0;
  virtual void execute();
};
