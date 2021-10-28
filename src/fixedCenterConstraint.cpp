#include "fixedCenterConstraint.h"
#include "circleRing.h"
#include "constraint.h"
#include "canvasManagerState.h"
#include "circleCenter.h"
#include <iostream>
#include <string>

FixedCenterConstraint::FixedCenterConstraint(CircleCenter *_center)
  : center(_center), fixedPos(center->getPos()) { }

FixedCenterConstraint::~FixedCenterConstraint() { }

bool FixedCenterConstraint::isConstraintBroken() {
  return center->getPos() != fixedPos;
}

bool FixedCenterConstraint::resolveConstraint(ShapePart *p,
                                              CanvasManagerState *state,
                                              set<ShapePart *> *resolved) {
  return !isConstraintBroken();
}

vector<ShapePart *> FixedCenterConstraint::getAllConstrainted() {
  return vector<ShapePart*>{ center };
}

void FixedCenterConstraint::draw(DrawManager *drawManager, ShapePart *part) {
  Point pos = center->getPos();
  int size = AppConsts::constraintIconSize;
  pos.y -= 1.1 * size;
  pos.x -= size/2;
  drawManager->drawRect(pos.x, pos.y, size, size, color);
  drawManager->drawImage(pos.x, pos.y, AppConsts::lockedIconImage);
}

bool FixedCenterConstraintCreator::canMakeConstraint(vector<ShapePart *> *parts,
                                                     CanvasManagerState *state){
  if(parts->size() != 1)
    return false;

  if(state->getConstraint((*parts)[0]) != nullptr)
    return false;

  return typeid(*(*parts)[0]) == typeid(CircleCenter);
}

bool FixedCenterConstraintCreator::makeConstraint(vector<ShapePart *> *parts,
                                                  CanvasManagerState *state){
  if(!canMakeConstraint(parts, state))
    return false;

  CircleCenter *center = dynamic_cast<CircleCenter*>((*parts)[0]);

  if(center == nullptr)
    return false;

  state->addConstraint(center, new FixedCenterConstraint(center));

  return true;
}
