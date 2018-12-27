# include "scene_graph.h"
# include <utility>
# include <algorithm>

/* ############################### Scene Node ############################### */

SceneNode::SceneNode(): parent(nullptr) {}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawCurrent(target, states);
    for (auto &child : children) child->draw(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {}

void SceneNode::updateCurrent(sf::Time dt) {}

void SceneNode::updateChildren(sf::Time dt) {
    for (auto &child : children) child->update(dt);
}

void SceneNode::attatchChild(std::unique_ptr<SceneNode> child) {
    child->parent = this;
    children.push_back(std::move(child));
}

std::unique_ptr<SceneNode> SceneNode::deatatchChild(const SceneNode &node) {
    auto found = std::find_if(children.begin(), children.end(),
    [&](std::unique_ptr<SceneNode> &p) -> bool { return p.get() == &node; });

    std::unique_ptr<SceneNode> result = std::move(*found);
    result->parent = nullptr;
    children.erase(found);
    return result;
}

void SceneNode::update(sf::Time dt) {
    updateCurrent(dt);
    updateChildren(dt);
}

sf::Transform SceneNode::getWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;

    const SceneNode *curNode = this;
    while (curNode != nullptr) {
        transform = curNode->getTransform() * transform;
        curNode = curNode->parent;
    }

    return transform;
}

/* ############################## Sprite Node ############################### */

SpriteNode::SpriteNode(const sf::Texture &texture): sprite(texture) {}

SpriteNode::SpriteNode(const sf::Texture &texture, const sf::IntRect &rect):
sprite(texture, rect) {}

void SpriteNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

/* ################################# Entity ################################# */

void Entity::updateCurrent(sf::Time dt) {
    move(velocity * dt.asSeconds());
}
