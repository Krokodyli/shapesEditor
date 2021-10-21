#include "defaultManagerMode.h"
#include <iostream>

DefaultManagerMode::DefaultManagerMode()
  : selectAction(false, true, true, Color(0, 0, 0), Color(255, 0, 0)) { } // TODO

void DefaultManagerMode::start(Canvas *canvas) {
  lastTimeClicked = getTime();
}

void DefaultManagerMode::update(Canvas *canvas, InputInfo *inputInfo) {
  mousePos = inputInfo->getMousePos();

  if(inputInfo->isLeftClicked()) {
    bool selectWholeShape = getTime() - lastTimeClicked <= 400; // TODO
    selectAction.select(inputInfo->getMousePos(), selectWholeShape);

    canvas->doAction(&selectAction);

    if(selectAction.isSomethingSelected())
      grabbed = true;

    lastTimeClicked = getTime();
  }

  if(inputInfo->isRightClicked()) {
    selectAction.deselect();
    canvas->doAction(&selectAction);
  }

  if(!inputInfo->isLeftPressed())
    grabbed = false;

  if(mousePos != oldMousePos && grabbed) {
    Move move(oldMousePos, mousePos);
    moveAction.move(&selectAction, move);
    canvas->doAction(&moveAction);
  }

  oldMousePos = mousePos;
}

void DefaultManagerMode::stop(Canvas *canvas) {
  selectAction.deselect();
  canvas->doAction(&selectAction);
}

int DefaultManagerMode::getTime() {
  return duration_cast<milliseconds>
    (system_clock::now().time_since_epoch()).count();
}
