#pragma once

#include <unordered_map>
#include "constraint.h"

using std::unordered_map;

class ShapePart;

class CanvasManagerState {
 private:
  unordered_map<ShapePart*, Constraint*> constraints;
 public:
  ~CanvasManagerState();
  unordered_map<ShapePart*, Constraint*> getConstraints();

  Constraint *getConstraint(ShapePart *part);
  void addConstraint(ShapePart *part, Constraint *constraint);
  void deleteConstraint(ShapePart *part);
};
