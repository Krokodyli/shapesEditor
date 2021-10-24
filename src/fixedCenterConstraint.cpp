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
                                              set<ShapePart *> resolved) {
  return !isConstraintBroken();
}

vector<ShapePart *> FixedCenterConstraint::getAllConstrainted() {
  return vector<ShapePart*>{ center };
}

void FixedCenterConstraint::draw(DrawManager *drawManager) {
  Point pos = center->getPos();
  pos.y -= 12;
  drawManager->drawRect(pos.x, pos.y, 25, 25, Color(255, 0, 0));
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

  if(center != nullptr) {
    state->addConstraint(center, new FixedCenterConstraint(center));
    return true;
  }
  else {
    return false;
  }
}
