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
    int score = 0;
    int speedLevel = 0;
    bool gameOver = false;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    float lastPlayerY = 0.0f;
    float enemyBaseSpeed = 5.0f;            
    const int SPEED_STEP = 1500;     // каждые 1500 очков — ускоряем
    const float SPEED_INCREMENT = 1.0f; // на сколько ускоряем
    sf::Text nearMissText;
    float nearMissTimer = 0.0f;
    const float NEAR_MISS_DURATION = 1.5f; // секунда и половина
    sf::Clock deltaClock;
private:
    void handleEvents();
    void update();
    void render();
    void spawnEnemy();
    void ResetGame();
};
