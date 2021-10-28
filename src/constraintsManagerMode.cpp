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

ConstraintsManagerMode::~ConstraintsManagerMode() {
  for(auto entry : constraintCreators)
    delete entry.second;
}

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
  auto constraint = constraintCreators.find(actionID);
  if(constraint != constraintCreators.end())
    constraint->second->makeConstraint(&selectedParts, state);
  else if (actionID == deleteConstraints)
    deleteConstraint();
  else
    return;

  selectAction.deselect();
  canvas->doAction(&selectAction);
}

bool ConstraintsManagerMode::canDoAction(Canvas *canvas, int actionID) {
  auto constraint = constraintCreators.find(actionID);
  if (constraint != constraintCreators.end())
    return constraint->second->canMakeConstraint(&selectedParts, state);
  else if (actionID == deleteConstraints)
    return canDeleteConstraint();
  else
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

void ConstraintsManagerMode::setupConstraintCreators() {
  std::pair<int, ConstraintCreator*> constraintCreatorsPairs[] = {
    { makeFixedCenterConstraint, new FixedCenterConstraintCreator() },
    { makeFixedRadiusConstraint, new FixedRadiusConstraintCreator() },
    { makeFixedLengthConstraint, new FixedLengthConstraintCreator() },
    { makeEqualEdgesConstraint, new EqualEdgesConstraintCreator() },
    { makeParallelEdgesConstraint, new ParallelEdgesConstraintCreator() },
    { makeTangentConstraint, new TangentConstraintCreator() }
  };

  for(auto pair : constraintCreatorsPairs)
    constraintCreators[pair.first] = pair.second;
}

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
