#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle {
public:
    Obstacle(const sf::Texture& texture, const sf::IntRect& textureRect, sf::Vector2f initialPosition);

    void update(float roadSpeed);
    void render(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
};

#endif
