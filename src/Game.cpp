#include "Game.h"
#include<iostream>
#include <cstdlib>
#include <ctime>
#include "Obstacle.h"

// costructor
//  member initializer list is window isRuning tehy are initalized befoe object creation 
Game::Game() : window(sf::VideoMode(1000,500),"Dino Game"), isRunning(true),timeDone(0.0f),score(0),roadSpeed(-0.2f){
    initialize();
}

Game::~Game(){
    std::cout<<"Game is ending";
}   

// Game loop fucntions

void Game::run(){
    while(isRunning){
        processEvents();
        update();
        render();
    }
}

// Handle Events
void Game::processEvents(){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            isRunning = false;
        }
    }
    dino.handleInput(event);
}

void Game::update(){
    float deltaTime = gloabalClock.getElapsedTime().asSeconds();
    gloabalClock.restart();
    timeDone += deltaTime;
    // std::cout<<score;

    if(timeDone >= 1.0f){
        timeDone = 0.0f;
        score++;
    }

    dino.update(roadSpeed);


    for (auto& obstacle : obstacles) {
        obstacle.update(roadSpeed);

    }


     // Check for collisions
    for (const auto& obstacle : obstacles) {
        if (dino.getBound().intersects(obstacle.getBounds())) {
            std::cout<<"Collide";
            // isRunning = false; // Game over
        }
    }

}

// Render Graphics
void Game::render(){
    window.clear(sf::Color::White);
    dino.render(window);

    // Draw Obstacles
    for (const auto& obstacle : obstacles) {
        obstacle.render(window);
    }

    window.display();
}

void Game::initialize(){
    gloabalClock.restart();

    srand(static_cast<unsigned int>(time(0)));

    if(!obstacleTexture.loadFromFile("resources/sprite.png")){
        std::cerr<<"Error loading obstacle \n";
    }

     for (int i = 0; i < 3; ++i) {
        spawnObstacle();
    }


    std::cout<<"Game initialized\n";
}

void Game::spawnObstacle(){
    std::vector<sf::IntRect> obstacleRects = {
        sf::IntRect(850,0,103,100),
        sf::IntRect(700,0,53,80),
        sf::IntRect(800,0,52,100),
    };

    int randomIndex = rand() % obstacleRects.size();

    // float randomX = 300 + rand() % 400;
    // float randomY = 360;

    Obstacle obstacle(obstacleTexture, obstacleRects[randomIndex],sf::Vector2f(2000 + rand()%700, 300));
    obstacles.push_back(obstacle);

}

