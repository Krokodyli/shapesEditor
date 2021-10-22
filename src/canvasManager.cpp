#include "canvasManager.h"
#include "canvas.h"
#include "defaultManagerMode.h"

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
