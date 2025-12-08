#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Game::Game(int width, int height)
    : window(sf::VideoMode(width, height), "Avoid Cars Game")
{
    window.setFramerateLimit(60);

    if (!playerTexture.loadFromFile("sprites/player-car.png")) exit(-1);
    if (!enemyTexture.loadFromFile("sprites/city-car.png")) exit(-1);
    if (!grassTexture.loadFromFile("sprites/grass.png")) exit(-1);

    track = new Track(400, width, height, grassTexture);
    player = new PlayerCar(playerTexture, width / 2 - 25, height - 120, 5.0f);

    srand(static_cast<unsigned>(time(0)));
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
    player->handleInput(track->getLeft(), track->getRight(), 0, 600);

    // Спавн врагов
    if (spawnClock.getElapsedTime().asSeconds() > 1.5f) {
        spawnEnemy();
        spawnClock.restart();
    }

    // Обновление врагов
    for (auto e : enemies) e->update();

    // Удаление врагов за экраном
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](EnemyCar* e) { return e->getSprite().getPosition().y > 600; }),
        enemies.end()
    );

    // Проверка столкновений
    for (auto e : enemies) {
        if (player->getBounds().intersects(e->getBounds())) {
            window.close();
        }
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    track->draw(window);
    window.draw(player->getSprite());
    for (auto e : enemies) window.draw(e->getSprite());
    window.display();
}

void Game::spawnEnemy() {
    auto lanes = track->getLanes();
    int laneIndex = rand() % lanes.size();
    enemies.push_back(new EnemyCar(enemyTexture, lanes[laneIndex], -100, 5.0f));
}
