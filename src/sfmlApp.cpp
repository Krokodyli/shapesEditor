#include "sfmlApp.h"
#include "sfmlDrawManager.h"
#include "SFMLInputInfo.h"

SFMLApp::~SFMLApp() {
  App::~App();
  delete window;
}

void SFMLApp::setup() {
  window = new sf::RenderWindow(sf::VideoMode(1200, 600, 32), "title",
                                sf::Style::Titlebar | sf::Style::Close); // TODO
  window->setFramerateLimit(60); // TODO
  drawManager = new SFMLDrawManager(window);
  inputInfo = new SFMLInputInfo(window);
  App::setup();
}

void SFMLApp::draw() {
  canvas->draw(drawManager);
  toolbar->draw(drawManager);
  window->display();
}

void SFMLApp::handleEvents() {
  sf::Event e;
  while (window->pollEvent(e)) {
    if (e.type == sf::Event::Closed)
      isRunning = false;
  }
}
