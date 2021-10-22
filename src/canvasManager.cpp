#include "canvasManager.h"
#include "canvas.h"
#include "constructManagerMode.h"
#include "constructionPolygon.h"
#include "defaultManagerMode.h"
#include "constructionCircle.h"
#include <iostream>

CanvasManager::CanvasManager(Canvas *_canvas) {
  canvas = _canvas;
  setup();
}

void CanvasManager::setMode(ManagerModeEnum newMode) {
  expectedMode = newMode;
}

ManagerModeEnum CanvasManager::getMode() {
  return currMode;
}

Canvas *CanvasManager::getCanvas() {
  return canvas;
}

void CanvasManager::setup() {
  modes[ManagerModeEnum::DefaultMode] = new DefaultManagerMode();
  modes[ManagerModeEnum::PolygonMode]
    = new ConstructManagerMode([](Canvas *canvas) {
      auto polygon = new ConstructionPolygon(canvas);
      return polygon;
    }, canvas);
  modes[ManagerModeEnum::CircleMode]
    = new ConstructManagerMode([](Canvas *canvas) {
      auto circle = new ConstructionCircle(canvas);
      return circle;
    }, canvas);

  expectedMode = ManagerModeEnum::DefaultMode;
  currMode = ManagerModeEnum::NoMode;
}

void CanvasManager::update(Canvas *canvas, InputInfo *inputInfo) {
  Point prevOffset = inputInfo->getOffset();
  inputInfo->setOffset(canvas->getPos());

  if(expectedMode != currMode) {
    if(currMode != ManagerModeEnum::NoMode)
      modes[currMode]->stop(canvas);
    currMode = expectedMode;
    if (currMode != ManagerModeEnum::NoMode)
      modes[currMode]->start(canvas);
  }
  if (currMode != ManagerModeEnum::NoMode)
    modes[currMode]->update(canvas, inputInfo);

  inputInfo->setOffset(prevOffset);
}
