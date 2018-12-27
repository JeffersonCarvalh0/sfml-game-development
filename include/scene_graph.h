# ifndef ENTITY_H
# define ENTITY_H

# include <SFML/Graphics.hpp>
# include <vector>
# include <memory>

class SceneNode : public sf::Transformable, public sf::Drawable,
                  private sf::NonCopyable {
private:
    std::vector<std::unique_ptr<SceneNode>> children;
    SceneNode *parent;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
    virtual void updateChildren(sf::Time dt);

public:
    SceneNode();
    void attatchChild(std::unique_ptr<SceneNode> child);
    std::unique_ptr<SceneNode> deatatchChild(const SceneNode &node);
    void update(sf::Time dt);
    sf::Transform getWorldTransform() const;
};

class SpriteNode : public SceneNode {
private:
    sf::Sprite sprite;

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    explicit SpriteNode(const sf::Texture &texture);
    SpriteNode(const sf::Texture &texture, const sf::IntRect &rect);
};

class Entity : public SceneNode {
public:
    virtual void updateCurrent(sf::Time dt);

public:
    sf::Vector2f velocity;
};

# endif /* end of include guard: ENTITY_H */
