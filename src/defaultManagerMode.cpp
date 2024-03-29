#include "defaultManagerMode.h"
#include "appConsts.h"

DefaultManagerMode::DefaultManagerMode(CanvasManagerState *_state)
  : ManagerMode(_state),
    selectAction(&selected, &selectedParts, false, true,
                 AppConsts::shapeColor, AppConsts::selectedShapeColor),
    moveAction(&selected, &selectedParts, state),
    deleteAction(&selected, &selectedParts, state),
    newVertexAction(&selected, &selectedParts, state) { }

void DefaultManagerMode::start(Canvas *canvas) { }

void DefaultManagerMode::update(Canvas *canvas, InputInfo *inputInfo) {
  auto mousePos = inputInfo->getMousePos();
  auto oldMousePos = inputInfo->getPrevMousePos();

  bool isMouseInsideCanvas = mousePos.insideRec(0, 0, canvas->getSize().x,
                                                canvas->getSize().y);

  if(inputInfo->isLeftClicked() && isMouseInsideCanvas) {
    bool selectWholeShape
      = inputInfo->wasLeftClickDouble(AppConsts::doubleClickThreshold);

    selectAction.select(inputInfo->getMousePos(), selectWholeShape);

    canvas->doAction(&selectAction);

    if(isSomethingSelected())
      grabbed = true;
  }

  if(inputInfo->isRightClicked()) {
    selectAction.deselect();
    canvas->doAction(&selectAction);
  }

  if(!inputInfo->isLeftPressed())
    grabbed = false;

  if(grabbed && mousePos != oldMousePos) {
    Move move(oldMousePos, mousePos);
    moveAction.move(move);
    canvas->doAction(&moveAction);
  }
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

void DefaultManagerMode::draw(DrawManager *drawManager, Canvas *canvas) {
  auto prevOffset = drawManager->getOffset();
  drawManager->setOffset(canvas->getPos());
  for(auto constraint : state->getConstraints())
    constraint.second->draw(drawManager, constraint.first);
  drawManager->setOffset(prevOffset);
}

const int DefaultManagerMode::deleteActionID = 0;
const int DefaultManagerMode::insertVertexActionID = 1;

bool DefaultManagerMode::isSomethingSelected() {
  return selected.size() > 0 || selectedParts.size() > 0;
}
