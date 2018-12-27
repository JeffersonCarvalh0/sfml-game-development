# ifndef AIRCRAFT_H
# define AIRCRAFT_H

# include <SFML/Graphics.hpp>
# include "resource_holder.hpp"
# include "scene_graph.h"

class Aircraft : public Entity {
public:
    enum Type { Eagle, Raptor };

private:
    Type type;
    sf::Sprite sprite;

public:
    Aircraft(Type type, const TextureHolder &textureHolder);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
};

# endif /* end of include guard: AIRCRAFT_H */
