#ifndef GAME_H
#define GAME_H

#include<SFML/Graphics.hpp>
#include "Dino.h"
#include "Obstacle.h"
#include <vector>

class Game{
    public:
        Game(); // constrcutor
        ~Game();    // destructor
        void run(); // main game loop
        // float getRoadSpeed() const;
        sf::Clock gloabalClock;

    private:
        void processEvents(); // handles keyboard/mouse events
        void update(); // update gameState textures and stuff
        void render();  // draws to the screen
        void initialize(); // initial states for all

        sf::RenderWindow window;  // game window
        Dino dino;  // main player for now
        long long score;
        float timeDone;
        float roadSpeed;
        bool isRunning; // game state tracker

        // obstacles
        std::vector<Obstacle> obstacles;
        sf::Texture obstacleTexture;

        void spawnObstacle();

};

#endif