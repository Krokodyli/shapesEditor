#include "fixedRadiusConstraint.h"
#include "constraint.h"
#include "canvasManagerState.h"
#include "circleCenter.h"
#include <string>

FixedRadiusConstraint::FixedRadiusConstraint(CircleRing *_ring)
  : ring(_ring), fixedRadius(ring->getR()) { }

FixedRadiusConstraint::~FixedRadiusConstraint() { }

bool FixedRadiusConstraint::isConstraintBroken() {
  return ring->getR() != fixedRadius;
}

bool FixedRadiusConstraint::resolveConstraint(ShapePart *p,
                                              CanvasManagerState *state,
                                              set<ShapePart *> *resolved) {
  return !isConstraintBroken();
}

vector<ShapePart *> FixedRadiusConstraint::getAllConstrainted() {
  return vector<ShapePart*>{ ring };
}

void FixedRadiusConstraint::draw(DrawManager *drawManager, ShapePart *part) {
  int size = AppConsts::constraintIconSize;
  Point pos = ring->getCenter()->getPos();
  pos.y -= ring->getR();
  pos.y -= size / 2;
  pos.x -= size / 2;
  drawManager->drawRect(pos.x, pos.y, size, size, color);
  drawManager->drawImage(pos.x, pos.y, AppConsts::lockedIconImage);
}

bool FixedRadiusConstraintCreator::canMakeConstraint(vector<ShapePart *> *parts,
                                                     CanvasManagerState *state){
  if(parts->size() != 1)
    return false;

  if(state->getConstraint((*parts)[0]) != nullptr)
    return false;

  return typeid(*(*parts)[0]) == typeid(CircleRing);
}

bool FixedRadiusConstraintCreator::makeConstraint(vector<ShapePart *> *parts,
                                                  CanvasManagerState *state){
  if(!canMakeConstraint(parts, state))
    return false;

  CircleRing *ring = dynamic_cast<CircleRing*>((*parts)[0]);

  if(ring == nullptr)
    return false;

  state->addConstraint((*parts)[0], new FixedRadiusConstraint(ring));

  return true;
}
