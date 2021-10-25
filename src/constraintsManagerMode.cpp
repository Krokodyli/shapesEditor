#include "constraintsManagerMode.h"
#include "fixedRadiusConstraint.h"
#include "fixedCenterConstraint.h"
#include "fixedLengthConstraint.h"
#include "equalEdgesConstraint.h"
#include "parallelEdgesConstraint.h"
#include "tangentConstraint.h"

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
  bool didAction = true;
  if(actionID == makeFixedRadiusConstraint) {
    FixedRadiusConstraintCreator creator;
    creator.makeConstraint(&selectedParts, state);
  }
  else if (actionID == makeFixedCenterConstraint) {
    FixedCenterConstraintCreator creator;
    creator.makeConstraint(&selectedParts, state);
  }
  else if (actionID == makeFixedLengthConstraint) {
    FixedLengthConstraintCreator creator;
    creator.makeConstraint(&selectedParts, state);
  }
  else if (actionID == makeEqualEdgesConstraint) {
    EqualEdgesConstraintCreator creator;
    creator.makeConstraint(&selectedParts, state);
  }
  else if (actionID == makeParallelEdgesConstraint) {
    ParallelEdgesConstraintCreator creator;
    creator.makeConstraint(&selectedParts, state);
  }
  else if (actionID == makeTangentConstraint) {
    TangentConstraintCreator creator;
    creator.makeConstraint(&selectedParts, state);
  }
  else if (actionID == deleteConstraints) {
    didAction = false;
    deleteConstraint();
  }
  else {
    didAction = false;
  }
  if(didAction) {
    selectAction.deselect();
    canvas->doAction(&selectAction);
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
  else if (actionID == makeFixedLengthConstraint) {
    FixedLengthConstraintCreator creator;
    return creator.canMakeConstraint(&selectedParts, state);
  }
  else if (actionID == makeEqualEdgesConstraint) {
    EqualEdgesConstraintCreator creator;
    return creator.canMakeConstraint(&selectedParts, state);
  }
  else if (actionID == makeParallelEdgesConstraint) {
    ParallelEdgesConstraintCreator creator;
    return creator.canMakeConstraint(&selectedParts, state);
  }
  else if (actionID == makeTangentConstraint) {
    TangentConstraintCreator creator;
    return creator.canMakeConstraint(&selectedParts, state);
  }
  else if (actionID == deleteConstraints) {
    return canDeleteConstraint();
  }

  return false;
}

void ConstraintsManagerMode::draw(DrawManager *drawManager, Canvas *canvas) {
  auto prevOffset = drawManager->getOffset();
  drawManager->setOffset(canvas->getPos());
  for(auto constraint : state->getConstraints())
    constraint.second->draw(drawManager, constraint.first);
  drawManager->setOffset(prevOffset);
}

const int ConstraintsManagerMode::makeFixedRadiusConstraint = 0;
const int ConstraintsManagerMode::makeFixedCenterConstraint = 1;
const int ConstraintsManagerMode::makeFixedLengthConstraint = 2;
const int ConstraintsManagerMode::makeEqualEdgesConstraint = 3;
const int ConstraintsManagerMode::makeParallelEdgesConstraint = 4;
const int ConstraintsManagerMode::makeTangentConstraint = 5;
const int ConstraintsManagerMode::deleteConstraints = 6;

void ConstraintsManagerMode::deleteConstraint() {
  if(!canDeleteConstraint())
    return;
  auto constraint = state->getConstraint(selectedParts[0]);
  if (constraint != nullptr)
    state->deleteConstraint(selectedParts[0]);
}

bool ConstraintsManagerMode::canDeleteConstraint() {
  if(selectedParts.size() != 1 || selected.size() != 0)
    return false;
  auto constraint = state->getConstraint(selectedParts[0]);
  return constraint != nullptr;
}
