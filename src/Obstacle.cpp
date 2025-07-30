#include "Obstacle.h"

Obstacle::Obstacle(const sf::Texture& texture, const sf::IntRect& textureRect, sf::Vector2f initialPosition) {
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect); // Set the specific section of the texture
    sprite.setPosition(initialPosition);
}

void Obstacle::update(float roadSpeed) {
    sprite.move(roadSpeed, 0);
    if (sprite.getPosition().x + sprite.getGlobalBounds().width < 0) {
        sprite.setPosition(1500 + rand()%400, sprite.getPosition().y); // Respawn on the right
    }
}

void Obstacle::render(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Obstacle::getBounds() const {
    return sprite.getGlobalBounds();
}
