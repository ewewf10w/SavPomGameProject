#pragma once
#include <SFML/Graphics.hpp>
#include "Car.h"
#include "Track.h"
#include "ScoreManager.h"
#include "Button.h"
#include <vector>

class Game {
private:
    sf::RenderWindow& window;
    sf::Texture playerTexture, enemyTexture, grassTexture;
    PlayerCar* player;
    std::vector<EnemyCar*> enemies;
    Track* track;
    sf::Clock spawnClock;

public:
    Game(sf::RenderWindow& win);
    ~Game();
    void run();

    float enemyBaseSpeed = 5.0f;

private:
    sf::Font font;
    sf::Text gameOverText;
    sf::Clock deltaClock;

    float lastPlayerY = 0.0f;
    bool gameOver = false;

    ScoreManager scoreManager;

private:
    void handleEvents();
    void update();
    void render();
    void spawnEnemy();
    void ResetGame();

    Button* restartButton = nullptr;
    Button* menuButton = nullptr;

    bool showGameOverMenu = false;
    bool backToMenu = false;
};
