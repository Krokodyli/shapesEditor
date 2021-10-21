#include "defaultManagerMode.h"
#include <iostream>

DefaultManagerMode::DefaultManagerMode()
  : selection(false, true, true, Color(0, 0, 0), Color(255, 0, 0)) { } // TODO

void DefaultManagerMode::start(Canvas *canvas) {
  lastTimeClicked = getTime();
}

void DefaultManagerMode::update(Canvas *canvas, InputInfo *inputInfo) {
  if(inputInfo->isLeftClicked()) {
    bool selectWholeShape = getTime() - lastTimeClicked <= 400; // TODO
    selection.select(inputInfo->getMousePos(), selectWholeShape);
    canvas->doAction(&selection);
    lastTimeClicked = getTime();
  }
  if(inputInfo->isRightClicked()) {
    selection.deselect();
    canvas->doAction(&selection);
  }
}

void DefaultManagerMode::stop(Canvas *canvas) {
  selection.deselect();
  canvas->doAction(&selection);
}

int DefaultManagerMode::getTime() {
  return duration_cast<milliseconds>
    (system_clock::now().time_since_epoch()).count();
}
