# include "world.h"
# include <utility>
# include <memory>

World::World(sf::RenderWindow &window):
window(window), worldView(window.getDefaultView()),
worldBounds(0.f, 0.f, worldView.getSize().x, 2000.f),
spawnPosition(worldView.getSize().x / 2.f, worldBounds.height - worldView.getSize().y / 2.f),
playerAircraft(nullptr) {
    loadTextures();
    buildScene();
    worldView.setCenter(spawnPosition);
}

void World::loadTextures() {
    textureHolder.load(Textures::Eagle, "../assets/textures/Eagle.png");
    textureHolder.load(Textures::Raptor, "../assets/textures/Raptor.png");
    textureHolder.load(Textures::Desert, "../assets/textures/Desert.png");
}

void World::buildScene() {
    // Initializing the layers
    for (int i = 0; i < LayerCount; ++i) {
        std::unique_ptr<SceneNode> layer(new SceneNode());
        sceneLayers[i] = layer.get();
        sceneGraph.attatchChild(std::move(layer));
    }

    // Loading background texture
    sf::Texture &texture = textureHolder.get(Textures::Desert);
    sf::IntRect textureRect(worldBounds);
    texture.setRepeated(true);

    // Creating a background node and attatching it to the scene graph
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
    sceneLayers[Background]->attatchChild(std::move(backgroundSprite));

    // Creating the player
    std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, textureHolder));
    playerAircraft = leader.get();
    playerAircraft->setPosition(spawnPosition);
    playerAircraft->velocity.x = 40.f; playerAircraft->velocity.y = scrollSpeed;
    sceneLayers[Air]->attatchChild(std::move(leader));

    // Creating the escort planes
    std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, textureHolder));
    leftEscort->setPosition(-80.f, 50.f);
    playerAircraft->attatchChild(std::move(leftEscort));

    std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, textureHolder));
    rightEscort->setPosition(80.f, 50.f);
    playerAircraft->attatchChild(std::move(rightEscort));
}

void World::update(sf::Time dt) {
    worldView.move(0.f, scrollSpeed * dt.asSeconds());

    sf::Vector2f position = playerAircraft->getPosition();
    sf::Vector2f velocity = playerAircraft->velocity;

    if (position.x <= worldBounds.left + 150 ||
    position.x >= worldBounds.left + worldBounds.width - 150) {
        velocity.x = -velocity.x;
        playerAircraft->velocity = velocity;
    }

    sceneGraph.update(dt);
}

void World::draw() {
    window.setView(worldView);
    window.draw(sceneGraph);
}
