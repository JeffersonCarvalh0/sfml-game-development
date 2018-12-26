# ifndef GAME_H
# define GAME_H

# include <SFML/Graphics.hpp>
# include "defs.h"
# include "resource_holder.hpp"

class Game {
private:
    sf::RenderWindow window;
    sf::Sprite player;
    ResourceHolder<sf::Texture, Textures> textureHolder;
    sf::Clock clock;
    bool isMovingUp, isMovingDown, isMovingLeft, isMovingRight;

private:
    void processEvents();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time deltaTime);
    void render();

public:
    Game();
    void run();
};

# endif /* end of include guard: GAME_H */
