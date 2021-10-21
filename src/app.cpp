#include "app.h"

App::App(Point _size) : size(_size) { }

App::~App() {
  delete canvas;
  delete canvasManager;
  delete canvasDrawManager;
  delete toolbar;
  delete inputInfo;
  delete drawManager;
}

void App::execute() {
  setup();
  isRunning = true;
  while(isRunning) {
    handleEvents();
    update();
    draw();
  }
}

void App::initialSetup() {
  canvasPos = Point(200, 0); // TODO
  canvasSize = size - canvasPos;
}

void App::setup() {
  canvas = new Canvas(canvasPos, canvasSize, canvasDrawManager);
  canvasManager = new CanvasManager();
  toolbar = new Toolbar();
}

void App::draw() {
  canvas->draw(drawManager);
  toolbar->draw(drawManager);
}

void App::update() {
  inputInfo->update();
  canvas->update(canvasManager, inputInfo);
}

void App::handleEvents() { }
