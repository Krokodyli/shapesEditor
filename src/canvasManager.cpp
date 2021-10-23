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

bool CanvasManager::canDoAction(ManagerModeEnum expectedMode, int actionID) {
  if(currMode == expectedMode)
    return modes[currMode]->canDoAction(canvas, actionID);
  else
    return false;
}

void CanvasManager::doAction(ManagerModeEnum expectedMode, int actionID) {
  if(currMode == expectedMode)
    modes[currMode]->doAction(canvas, actionID);
}

void CanvasManager::setup() {
  modes[ManagerModeEnum::DefaultMode] = new DefaultManagerMode(&state);
  modes[ManagerModeEnum::PolygonMode]
    = new ConstructManagerMode(&state, [](Canvas *canvas) {
      auto polygon = new ConstructionPolygon(canvas);
      return polygon;
    }, canvas);
  modes[ManagerModeEnum::CircleMode]
    = new ConstructManagerMode(&state, [](Canvas *canvas) {
      auto circle = new ConstructionCircle(canvas);
      return circle;
    }, canvas);

  modes[ManagerModeEnum::ConstraintMode]
    = new ConstraintsManagerMode(&state);

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

void CanvasManager::draw(DrawManager *drawManager) {
  if(currMode != ManagerModeEnum::NoMode)
    modes[currMode]->draw(drawManager, canvas);
}
