#ifndef DINO_H
#define DINO_H

#include<SFML/Graphics.hpp>

class Dino{
    public:
        Dino();
        void handleInput(const sf::Event &event);
        void update(float roadSpeed);
        void render(sf::RenderWindow &window);
        sf::FloatRect getBound() const;

    private:
        int score;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::IntRect frameRect;

        // for road
        sf::IntRect roadRect;
        sf::Sprite roadSprite;

        sf::Clock animationClock;
        float animationTime;
        float framDuration;
        int currentTime;
        int TotalFrames;


        // for jumping 
        bool isJumping;
        bool isFalling;
        float jumpVelocity;   // Initial upward velocity
        float gravity;        // Downward acceleration
        float groundLevel;  
        bool isCrouching;

};


#endif