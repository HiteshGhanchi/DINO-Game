#include "Dino.h"
#include "Game.h"
#include <iostream>

// Animation thing

Dino::Dino()
    : animationTime(0.0f) ,framDuration(0.1f),currentTime(0),TotalFrames(3),
     isJumping(false), isFalling(false), jumpVelocity(-400.0f), gravity(600.0f), groundLevel(300.0f),isCrouching(false) {
    if(!texture.loadFromFile("resources/sprite.png")){
        std::cerr<<"Error Loadinf texture form file\n";
    }
    sprite.setTexture(texture);
    // std::cout<<texture.getSize().x;
    frameRect = sf::IntRect(1426,0,88,100);
    roadRect = sf::IntRect(0,100,texture.getSize().x,300);
    // part of the texture, left , top, width , height

    roadSprite.setTexture(texture);
    roadSprite.setTextureRect(roadRect);
    roadSprite.setPosition(0,360);

    sprite.setTextureRect(frameRect);
    sprite.setPosition(300,300); // initial position
    animationClock.restart();
}

void Dino::handleInput(const sf::Event &event) {
    // Handle KeyPressed events
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            if (!isJumping && !isFalling) {
                isJumping = true;
            }
        }

        if (event.key.code == sf::Keyboard::Down) {
            isCrouching = true;
        }
    }

    // Handle KeyReleased events
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Down) {
            isCrouching = false;
        }
    }
}

void Dino::update(float roadSpeed){
    
    float deltaTime = animationClock.getElapsedTime().asSeconds();
    animationClock.restart(); // Restart the clock after each frame
    
    animationTime += deltaTime;

     if (isCrouching && !isJumping && !isFalling) {
        // Set crouch animation frame
        sprite.setTextureRect( sf::IntRect(1980, 0, 120, 100));
    } else if (!isJumping && !isFalling) {
        // Animate running
        if (animationTime > framDuration) {
            animationTime = 0.0f;

            currentTime = (currentTime + 1) % TotalFrames;
            frameRect.left = 1426 + currentTime * frameRect.width;
            sprite.setTextureRect(frameRect);
        }
    }

    

     // Jump logic
    if (isJumping) {
        sprite.move(0, jumpVelocity * deltaTime);
        jumpVelocity += gravity * deltaTime;

        // Transition to falling phase
        if (jumpVelocity >= 0) {
            isJumping = false;
            isFalling = true;
        }
    } else if (isFalling) {
        sprite.move(0, jumpVelocity * deltaTime);
        jumpVelocity += gravity * deltaTime;

        // End fall when Dino reaches the ground
        if (sprite.getPosition().y >= groundLevel) {
            sprite.setPosition(sprite.getPosition().x, groundLevel);
            isFalling = false;
            jumpVelocity = -400.0f; // Reset jump velocity
        }
    }


    // Move the road to the left
    roadSprite.move(roadSpeed, 0);

    // If the road has moved off the left side of the screen, reset it to the right
    if (roadSprite.getPosition().x + roadSprite.getGlobalBounds().width < 1000) {
        roadSprite.setPosition(0, 360);
    }


}

void Dino::render(sf::RenderWindow &window){
    window.draw(roadSprite);
    window.draw(sprite);

}

sf::FloatRect Dino::getBound() const{
    return sprite.getGlobalBounds();
}