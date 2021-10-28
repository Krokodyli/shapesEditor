#include "constraint.h"

Constraint::Constraint() {
  color = Color((rand() % 255 + 255) / 2, (rand() % 255 + 255) / 2,
                (rand() % 255 + 255) / 2);
}

Constraint::~Constraint() { }

ConstraintCreator::~ConstraintCreator() { }
