#pragma once
#include <SFML/Graphics.hpp>
#include "Car.h"
#include "Track.h"
#include <vector>

class Game {
private:
    sf::RenderWindow window;
    sf::Texture playerTexture, enemyTexture, grassTexture;
    PlayerCar* player;
    std::vector<EnemyCar*> enemies;
    Track* track;
    sf::Clock spawnClock;
public:
    Game(int width, int height);
    ~Game();
    void run();
private:
    void handleEvents();
    void update();
    void render();
    void spawnEnemy();
};
