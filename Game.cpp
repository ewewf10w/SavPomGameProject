#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

Game::Game(int width, int height)
    : window(sf::VideoMode(width, height), "Avoid Cars Game")
{
    window.setFramerateLimit(60);

    if (!playerTexture.loadFromFile("sprites/player-car.png")) exit(-1);
    if (!enemyTexture.loadFromFile("sprites/city-car.png")) exit(-1);
    if (!grassTexture.loadFromFile("sprites/grass.png")) exit(-1);

    font.loadFromFile("fonts/race-master.ttf");

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER\nPress R to restart");
    gameOverText.setPosition(250, 200);

    scoreManager.setFont(font);

    track = new Track(400, width, height, grassTexture);
    player = new PlayerCar(playerTexture, width / 2 - 25, height - 120, 5.0f);

    srand(static_cast<unsigned>(time(0)));

    enemyBaseSpeed = 5.0f;
    lastPlayerY = player->getSprite().getPosition().y;
    deltaClock.restart();
}

Game::~Game() {
    delete player;
    delete track;
    for (auto e : enemies) delete e;
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update() {
    float dt = deltaClock.restart().asSeconds();

    scoreManager.update(dt);

    if (gameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            ResetGame();
        }
        return;
    }

    lastPlayerY = player->getSprite().getPosition().y;
    for (auto e : enemies) e->lastY = e->getSprite().getPosition().y;

    player->handleInput(track->getLeft(), track->getRight(), 0, 600);

    if (spawnClock.getElapsedTime().asSeconds() > 1.5f) {
        spawnEnemy();
        spawnClock.restart();
    }

    for (auto e : enemies) e->update();

    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](EnemyCar* e) { return e->getSprite().getPosition().y > 600; }),
        enemies.end()
    );

    float playerY = player->getSprite().getPosition().y;
    float playerX = player->getSprite().getPosition().x;

    const float CLOSE_OVERTAKE_DIST = 100.0f;

    for (auto e : enemies) {
        if (!e->getWasNearMiss()) {
            if (lastPlayerY >= e->lastY && playerY < e->getSprite().getPosition().y) {

                float ex = e->getSprite().getPosition().x;
                float dx = fabs(playerX - ex);

                if (dx <= CLOSE_OVERTAKE_DIST) {
                    e->setWasNearMiss(true);
                    scoreManager.triggerNearMiss({ playerX, playerY });
                }
                else {
                    e->setWasNearMiss(true);
                    scoreManager.addScore(100);
                }
            }
        }
    }

    int levelsToAdd = scoreManager.consumeSpeedIncrease();
    if (levelsToAdd > 0) {
        const float SPEED_INCREMENT = 1.0f;
        enemyBaseSpeed += levelsToAdd * SPEED_INCREMENT;
        for (auto e : enemies) e->addSpeed(levelsToAdd * SPEED_INCREMENT);
    }

    for (auto e : enemies) {
        if (player->getBounds().intersects(e->getBounds())) {
            gameOver = true;
        }
    }
}

void Game::render() {
    window.clear(sf::Color::Black);

    track->draw(window);
    window.draw(player->getSprite());
    for (auto e : enemies) window.draw(e->getSprite());

    scoreManager.draw(window);

    if (gameOver) window.draw(gameOverText);

    window.display();
}

void Game::spawnEnemy() {
    auto lanes = track->getLanes();
    int laneIndex = rand() % lanes.size();
    enemies.push_back(new EnemyCar(enemyTexture, lanes[laneIndex], -100, enemyBaseSpeed));
}

void Game::ResetGame() {
    scoreManager.reset();
    gameOver = false;

    player->getSprite().setPosition(800 / 2 - 25, 600 - 120);

    for (auto e : enemies) delete e;
    enemies.clear();

    spawnClock.restart();

    enemyBaseSpeed = 5.0f;
}
