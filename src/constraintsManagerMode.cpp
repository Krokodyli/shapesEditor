#include "constraintsManagerMode.h"
#include "fixedRadiusConstraint.h"
#include "fixedCenterConstraint.h"

ConstraintsManagerMode::ConstraintsManagerMode(CanvasManagerState *_state)
  : ManagerMode(_state),
    selectAction(&selected, &selectedParts, true, true,
                 AppConsts::shapeColor, AppConsts::selectedShapeColor) { }

ConstraintsManagerMode::~ConstraintsManagerMode() { }

void ConstraintsManagerMode::start(Canvas *canvas) { }

void ConstraintsManagerMode::update(Canvas *canvas, InputInfo *inputInfo) {
  auto mousePos = inputInfo->getMousePos();
  bool isMouseInsideCanvas =
      mousePos.insideRec(0, 0, canvas->getSize().x, canvas->getSize().y);

  if(inputInfo->isLeftClicked() && isMouseInsideCanvas) {
    selectAction.select(mousePos);
    canvas->doAction(&selectAction);
  }
}

void ConstraintsManagerMode::stop(Canvas *canvas) {
  selectAction.deselect();
  canvas->doAction(&selectAction);
}

void ConstraintsManagerMode::doAction(Canvas *canvas, int actionID) {
  if(actionID == makeFixedRadiusConstraint) {
    FixedRadiusConstraintCreator creator;
    creator.makeConstraint(&selectedParts, state);
  }
  if (actionID == makeFixedCenterConstraint) {
    FixedCenterConstraintCreator creator;
    creator.makeConstraint(&selectedParts, state);
  }
}

bool ConstraintsManagerMode::canDoAction(Canvas *canvas, int actionID) {
  if (actionID == makeFixedRadiusConstraint) {
    FixedRadiusConstraintCreator creator;
    return creator.canMakeConstraint(&selectedParts, state);
  }
  else if(actionID == makeFixedCenterConstraint) {
    FixedCenterConstraintCreator creator;
    return creator.canMakeConstraint(&selectedParts, state);
  }
  return false;
}

void ConstraintsManagerMode::draw(DrawManager *drawManager, Canvas *canvas) {
  auto prevOffset = drawManager->getOffset();
  drawManager->setOffset(canvas->getPos());
  for(auto constraint : state->getConstraints())
    constraint.second->draw(drawManager);
  drawManager->setOffset(prevOffset);
}

const int ConstraintsManagerMode::makeFixedRadiusConstraint = 0;
const int ConstraintsManagerMode::makeFixedCenterConstraint = 1;
