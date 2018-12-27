# ifndef WORLD_H
# define WORLD_H

# include <SFML/Graphics.hpp>
# include <array>
# include "aircraft.h"
# include "resource_holder.hpp"
# include "scene_graph.h"

class World : private sf::NonCopyable {
private:
    enum Layer { Background, Air, LayerCount };

private:
    sf::RenderWindow &window;
    sf::View worldView;
    TextureHolder textureHolder;
    SceneNode sceneGraph;
    std::array<SceneNode*, LayerCount> sceneLayers;

    sf::FloatRect worldBounds;
    sf::Vector2f spawnPosition;
    float scrollSpeed;
    Aircraft *playerAircraft;

private:
    void loadTextures();
    void buildScene();

public:
    explicit World(sf::RenderWindow &window);
    void update(sf::Time dt);
    void draw();
};

# endif /* end of include guard: WORLD_H */
