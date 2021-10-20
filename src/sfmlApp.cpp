#include "sfmlApp.h"
#include "sfmlDrawManager.h"
#include "SFMLInputInfo.h"
#include "sfmlCanvasDrawManager.h"

SFMLApp::SFMLApp(Point _size) : App(_size) { }

SFMLApp::~SFMLApp() {
  App::~App();
  delete window;
}

void SFMLApp::setup() {
  App::initialSetup();
  window = new sf::RenderWindow(sf::VideoMode(size.x, size.y, 32),
                                "title", sf::Style::Titlebar |
                                sf::Style::Close); // TODO
  window->setFramerateLimit(60); // TODO
  drawManager = new SFMLDrawManager(window);
  inputInfo = new SFMLInputInfo(window);
  canvasDrawManager = new SFMLCanvasDrawManager(canvasSize);
  App::setup();
}

void SFMLApp::draw() {
  toolbar->draw(drawManager);
  drawManager->drawCircle(175, 100, 50, Color(0, 0, 255));
  canvas->draw(drawManager);
  window->display();
}

void SFMLApp::handleEvents() {
  sf::Event e;
  while (window->pollEvent(e)) {
    if (e.type == sf::Event::Closed)
      isRunning = false;
  }
}
