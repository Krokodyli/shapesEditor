#include "defaultManagerMode.h"
#include "appConsts.h"

DefaultManagerMode::DefaultManagerMode()
    : selectAction(&selected, &selectedParts, false, true, true,
                   AppConsts::shapeColor, AppConsts::selectedShapeColor),
      moveAction(&selected, &selectedParts),
      deleteAction(&selected, &selectedParts),
      newVertexAction(&selected, &selectedParts) { }

void DefaultManagerMode::start(Canvas *canvas) {
  lastTimeClicked = getTime();
}

void DefaultManagerMode::update(Canvas *canvas, InputInfo *inputInfo) {
  mousePos = inputInfo->getMousePos();
  bool isMouseInsideCanvas = mousePos.insideRec(0, 0, canvas->getSize().x,
                                                canvas->getSize().y);

  if(inputInfo->isLeftClicked() && isMouseInsideCanvas) {
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

void DefaultManagerMode::doAction(Canvas *canvas, int actionID) {
  if(!canDoAction(canvas, actionID))
    return;

  if (actionID == deleteActionID) {
    canvas->doAction(&deleteAction);
  }
  else if (actionID == insertVertexActionID) {
    canvas->doAction(&newVertexAction);
    selectAction.deselect();
    canvas->doAction(&selectAction);
  }
}

bool DefaultManagerMode::canDoAction(Canvas *canvas, int actionID) {
  if(actionID == deleteActionID)
    return canvas->canDoAction(&deleteAction);
  else if (actionID == insertVertexActionID)
    return canvas->canDoAction(&newVertexAction);
  else
    return false;
}

const int DefaultManagerMode::deleteActionID = 0;
const int DefaultManagerMode::insertVertexActionID = 1;

int DefaultManagerMode::getTime() {
  return duration_cast<milliseconds>
    (system_clock::now().time_since_epoch()).count();
}

bool DefaultManagerMode::isSomethingSelected() {
  return selected.size() > 0 || selectedParts.size() > 0;
}
