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

    font.loadFromFile("fonts/race-master.ttf");

    nearMissText.setFont(font);
    nearMissText.setCharacterSize(40);
    nearMissText.setFillColor(sf::Color::Yellow);
    nearMissText.setStyle(sf::Text::Bold);
    nearMissText.setString(""); // пусто по умолчанию
    nearMissText.setPosition(300, 150); // можно менять
    nearMissTimer = 0.0f;

    // и сбросим deltaClock
    deltaClock.restart();

    scoreText.setFont(font);
    scoreText.setCharacterSize(32);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20, 20);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER\nPress R to restart");
    gameOverText.setPosition(250, 200);

    track = new Track(400, width, height, grassTexture);
    player = new PlayerCar(playerTexture, width / 2 - 25, height - 120, 5.0f);

    srand(static_cast<unsigned>(time(0)));

    enemyBaseSpeed = 5.0f;
    lastPlayerY = player->getSprite().getPosition().y;
    speedLevel = 0;
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
    // dt
    float dt = deltaClock.restart().asSeconds();

    // Если игра окончена — как у тебя уже есть
    if (gameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            ResetGame();
        }
        return;
    }

    // --- сохраняем предыдущие Y ---
    lastPlayerY = player->getSprite().getPosition().y;
    for (auto e : enemies) e->lastY = e->getSprite().getPosition().y;

    // --- управление игроком и спавн (как раньше) ---
    player->handleInput(track->getLeft(), track->getRight(), 0, 600);

    if (spawnClock.getElapsedTime().asSeconds() > 1.5f) {
        spawnEnemy();
        spawnClock.restart();
    }

    for (auto e : enemies) e->update();

    // удаление за экраном (как было)
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](EnemyCar* e) { return e->getSprite().getPosition().y > 600; }),
        enemies.end()
    );

    // ---- ОБГОН: проверка момента пересечения + близость по X ----
    float playerY = player->getSprite().getPosition().y;
    float playerX = player->getSprite().getPosition().x;

    const float CLOSE_OVERTAKE_DIST = 100.0f; // порог по X
    const float VERT_CLOSE_THRESHOLD = 100.0f; // вертикальная близость (если нужно)

    for (auto e : enemies) {
        // проверяем, что обгон состоялся в этом кадре:
        if (!e->getWasNearMiss()) {
            // проверка пересечения: раньше игрок был ниже/ровно, теперь игрок выше => обогнал
            if (lastPlayerY >= e->lastY && playerY < e->getSprite().getPosition().y) {

                float ex = e->getSprite().getPosition().x;
                float dx = fabs(playerX - ex);

                if (dx <= CLOSE_OVERTAKE_DIST) {
                    // близкий обгон — бонус
                    score += 200;
                    e->setWasNearMiss(true);

                    // показать надпись на экране
                    nearMissText.setString("NEAR MISS! +200");
                    // позиционируем над игроком (пример)
                    nearMissText.setPosition(playerX - 60, playerY - 80);
                    nearMissTimer = NEAR_MISS_DURATION;
                }
                else {
                    // обычный обгон
                    score += 100;
                    e->setWasNearMiss(true);
                }
            }
        }
    }

    // ---- ускорение машин по очкам (как у тебя) ----
    int newLevel = score / SPEED_STEP;
    if (newLevel > speedLevel) {
        int levelsToAdd = newLevel - speedLevel;
        speedLevel = newLevel;
        enemyBaseSpeed += levelsToAdd * SPEED_INCREMENT;
        for (auto e : enemies) e->addSpeed(levelsToAdd * SPEED_INCREMENT);
    }

    // ---- коллизии ----
    for (auto e : enemies) {
        if (player->getBounds().intersects(e->getBounds())) {
            gameOver = true;
        }
    }

    // ---- обновляем таймер надписи NEAR MISS ----
    if (nearMissTimer > 0.0f) {
        nearMissTimer -= dt;
        if (nearMissTimer <= 0.0f) {
            nearMissTimer = 0.0f;
            nearMissText.setString("");
        }
    }
}

void Game::render() {
    window.clear(sf::Color::Black);

    track->draw(window);
    window.draw(player->getSprite());
    for (auto e : enemies) window.draw(e->getSprite());

    // --- SCORE TEXT ---
    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);

    // рисуем near miss, если активен
    if (nearMissTimer > 0.0f) {
        window.draw(nearMissText);
    }

    // рисуем game over, если нужно
    if (gameOver) window.draw(gameOverText);

    window.display();
}

void Game::spawnEnemy() {
    auto lanes = track->getLanes();
    int laneIndex = rand() % lanes.size();
    enemies.push_back(new EnemyCar(enemyTexture, lanes[laneIndex], -100, enemyBaseSpeed));
}

void Game::ResetGame() {
    score = 0;
    gameOver = false;

    // Respawn player
    player->getSprite().setPosition(800 / 2 - 25, 600 - 120);

    // Respawn enemies
    for (auto e : enemies) delete e;
    enemies.clear();

    spawnClock.restart();

    // Сброс уровня скорости
    enemyBaseSpeed = 5.0f;
    speedLevel = 0;
}
