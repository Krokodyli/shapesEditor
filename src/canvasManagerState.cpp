#include "canvasManagerState.h"
#include "constraint.h"
#include <unordered_map>

CanvasManagerState::~CanvasManagerState() {
  for(auto entry : constraints)
    delete entry.second;
}


unordered_map<ShapePart*, Constraint*> CanvasManagerState::getConstraints() {
  return constraints;
}

Constraint *CanvasManagerState::getConstraint(ShapePart *part) {
  auto found = constraints.find(part);
  if(found == constraints.end())
    return nullptr;
  else
    return found->second;
}

void CanvasManagerState::addConstraint(ShapePart *part, Constraint *constraint) {
  constraints.emplace(part, constraint);
}

void CanvasManagerState::deleteConstraint(ShapePart *part) {
  auto found = constraints.find(part);
  if(found != constraints.end()) {
    auto constraint = found->second;
    auto constrainted = constraint->getAllConstrainted();
    for(auto shapePart : constrainted)
      constraints.erase(shapePart);
    delete constraint;
  }
}
