# include "game.h"

Game::Game(): window(sf::VideoMode(640, 480), "SFML Application"), world(window) {
    isMovingUp = isMovingDown = isMovingLeft = isMovingRight = false;
}

void Game::run() {
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen()) {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;

    while(window.pollEvent(event)) {
        switch(event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true); break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false); break;
            case sf::Event::Closed:
                window.close(); break;
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W) isMovingUp = isPressed;
    if (key == sf::Keyboard::S) isMovingDown = isPressed;
    if (key == sf::Keyboard::A) isMovingLeft = isPressed;
    if (key == sf::Keyboard::D) isMovingRight = isPressed;
}

void Game::update(sf::Time deltaTime) {
    world.update(deltaTime);
}

void Game::render() {
    window.clear();
    world.draw();
    window.display();
}
