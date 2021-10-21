#include "defaultManagerMode.h"
#include <iostream>

DefaultManagerMode::DefaultManagerMode()
  : selection(false, true, true, Color(0, 0, 0), Color(255, 0, 0)) { } // TODO

void DefaultManagerMode::start(Canvas *canvas) { }

void DefaultManagerMode::update(Canvas *canvas, InputInfo *inputInfo) {
  if(inputInfo->isLeftClicked()) {
    selection.select(inputInfo->getMousePos());
    canvas->doAction(&selection);
  }
}

void DefaultManagerMode::stop(Canvas *canvas) { }
