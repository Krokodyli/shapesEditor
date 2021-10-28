#include "constraint.h"

Constraint::Constraint() {
  color = AppConsts::getRandomColorForConstraint();
}

Constraint::~Constraint() { }

ConstraintCreator::~ConstraintCreator() { }
