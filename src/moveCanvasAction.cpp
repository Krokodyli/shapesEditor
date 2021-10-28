#include "moveCanvasAction.h"
#include "constraint.h"
#include "moveAction.h"

MoveCanvasAction::MoveCanvasAction(vector<Shape *> *_shapes,
                                   vector<ShapePart *> *_shapeParts,
                                   CanvasManagerState *_state)
  : shapes(_shapes), shapeParts(_shapeParts), state(_state) {
  maxMoveDelta = 2;
}

void MoveCanvasAction::move(Move _move) {
  moveValue = _move;
}

void MoveCanvasAction::doAction(std::vector<Shape *> *_shapes) {
  MoveAction moveAction;
  vector<Move> moves = splitMove();
  for(auto move : moves) {
    moveAction.moveShape(move, state);

    for(auto shape : *shapes)
      shape->doAction(&moveAction);

    for (auto shapePart : *shapeParts) {
      moveAction.moveShape(move, state, shapePart);
      shapePart->getParent()->doAction(&moveAction);
    }
  }
}

bool MoveCanvasAction::canDoAction(std::vector<Shape *> *_shapes) {
  return false;
}

vector<Move> MoveCanvasAction::splitMove() {
  vector<Move> moves;
  int n = 1;
  while((moveValue.delta / n).x > maxMoveDelta
        || (moveValue.delta / n).y > maxMoveDelta) n++;

  Point mousePos = moveValue.oldMousePos;

  for(int i = 0; i < n; i++) {
    moves.push_back(Move(mousePos, mousePos + (moveValue.delta / n)));
    mousePos = mousePos + (moveValue.delta / n);
  }

  if(moves[moves.size() - 1].newMousePos != moveValue.newMousePos)
    moves.push_back(Move(moves[moves.size()-1].newMousePos,
                         moveValue.newMousePos));

  return moves;
}
