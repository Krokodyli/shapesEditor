#include "defaultManagerMode.h"
#include "appConsts.h"

DefaultManagerMode::DefaultManagerMode()
    : selectAction(&selected, &selectedParts, false, true, true,
                   AppConsts::shapeColor, AppConsts::selectedShapeColor),
      moveAction(&selected, &selectedParts) { }

void DefaultManagerMode::start(Canvas *canvas) {
  lastTimeClicked = getTime();
}

void DefaultManagerMode::update(Canvas *canvas, InputInfo *inputInfo) {
  mousePos = inputInfo->getMousePos();

  if(inputInfo->isLeftClicked()) {
    bool selectWholeShape =
      getTime() - lastTimeClicked <= AppConsts::doubleClickThreshold;

    selectAction.select(inputInfo->getMousePos(), selectWholeShape);

    canvas->doAction(&selectAction);

    if(isSomethingSelected())
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
    moveAction.move(move);
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

bool DefaultManagerMode::isSomethingSelected() {
  return selected.size() > 0 || selectedParts.size() > 0;
}
