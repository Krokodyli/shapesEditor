#include "canvasManager.h"
#include "canvas.h"
#include "constructManagerMode.h"
#include "constructionCircle.h"
#include "constructionPolygon.h"
#include "defaultManagerMode.h"
#include "fixedCenterConstraint.h"
#include "fixedLengthConstraint.h"
#include <iostream>
#include "fixedRadiusConstraint.h"
#include "parallelEdgesConstraint.h"
#include "equalEdgesConstraint.h"
#include "tangentConstraint.h"

CanvasManager::CanvasManager(Canvas *_canvas) {
  canvas = _canvas;
  setup();
  setupSomeShapes();
}

void CanvasManager::setMode(ManagerModeEnum newMode) {
  expectedMode = newMode;
}

ManagerModeEnum CanvasManager::getMode() {
  return currMode;
}

Canvas *CanvasManager::getCanvas() {
  return canvas;
}

bool CanvasManager::canDoAction(ManagerModeEnum expectedMode, int actionID) {
  if(currMode == expectedMode)
    return modes[currMode]->canDoAction(canvas, actionID);
  else
    return false;
}

void CanvasManager::doAction(ManagerModeEnum expectedMode, int actionID) {
  if(currMode == expectedMode)
    modes[currMode]->doAction(canvas, actionID);
}

void CanvasManager::setup() {
  modes[ManagerModeEnum::DefaultMode] = new DefaultManagerMode(&state);
  modes[ManagerModeEnum::PolygonMode]
    = new ConstructManagerMode(&state, [](Canvas *canvas) {
      auto polygon = new ConstructionPolygon(canvas);
      return polygon;
    }, canvas);
  modes[ManagerModeEnum::CircleMode]
    = new ConstructManagerMode(&state, [](Canvas *canvas) {
      auto circle = new ConstructionCircle(canvas);
      return circle;
    }, canvas);

  modes[ManagerModeEnum::ConstraintMode]
    = new ConstraintsManagerMode(&state);

  expectedMode = ManagerModeEnum::DefaultMode;
  currMode = ManagerModeEnum::NoMode;
}

void CanvasManager::update(Canvas *canvas, InputInfo *inputInfo) {
  Point prevOffset = inputInfo->getOffset();
  inputInfo->setOffset(canvas->getPos());

  if(expectedMode != currMode) {
    if(currMode != ManagerModeEnum::NoMode)
      modes[currMode]->stop(canvas);
    currMode = expectedMode;
    if (currMode != ManagerModeEnum::NoMode)
      modes[currMode]->start(canvas);
  }
  if (currMode != ManagerModeEnum::NoMode)
    modes[currMode]->update(canvas, inputInfo);

  inputInfo->setOffset(prevOffset);
}

void CanvasManager::draw(DrawManager *drawManager) {
  if(currMode != ManagerModeEnum::NoMode)
    modes[currMode]->draw(drawManager, canvas);
}

void CanvasManager::setupSomeShapes() {
  auto p1 = canvas->addPolygon(vector<Point>{
      Point(100, 200),
      Point(125, 100),
      Point(300, 300),
      Point(200, 350)
  });
  EqualEdgesConstraintCreator p1c;
  auto p1e1 = p1->getHead()->getA();
  auto p1e2 = p1e1->getB()->getB()->getB()->getB();
  vector<ShapePart*> p1v{p1e1, p1e2};
  p1c.makeConstraint(&p1v, &state);

  auto c1 = canvas->addCircle(Point(600, 600), 75);
  state.addConstraint(c1->getCenter(),
                      new FixedCenterConstraint(c1->getCenter()));

  auto p2 = canvas->addPolygon(vector<Point>{
      Point(500, 100),
      Point(700, 100),
      Point(700, 300),
      Point(500, 300)
    });
  auto p2e1 = p2->getHead()->getA()->getA()->getA()->getA()->getA();
  auto c2 = canvas->addCircle(Point(525, 250), 50);
  vector<ShapePart*> p2v{p2e1, c2->getRing()};
  TangentConstraintCreator p2c;
  p2c.makeConstraint(&p2v, &state);

  auto c3 = canvas->addCircle(Point(900, 800), 20);
  state.addConstraint(c3->getRing(),
                      new FixedRadiusConstraint(c3->getRing()));

  auto p3 = canvas->addPolygon(vector<Point>{
      Point(400, 400),
      Point(440, 440),
      Point(480, 400),
      Point(400, 350)
    });

  auto p3e1 = p3->getHead()->getB()->getB()->getB();
  auto p3e2 = p3->getHead()->getA();
  vector<ShapePart*> p3v{ p3e1, p3e2 };
  ParallelEdgesConstraintCreator p3c;
  p3c.makeConstraint(&p3v, &state);

  auto p4 = canvas->addPolygon(vector<Point>{Point(400, 800), Point(600, 800),
                                             Point(600, 850), Point(400, 850)});
  (void)p4;
  auto p4e1 = p4->getHead()->getA();
  state.addConstraint(p4e1, new FixedLengthConstraint(p4e1));
}
