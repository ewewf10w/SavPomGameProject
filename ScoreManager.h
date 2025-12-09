#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ScoreManager {
public:
    ScoreManager();

    void setFont(const sf::Font& f);

    void addScore(int s);
    int getScore() const;

    void triggerNearMiss(const sf::Vector2f& pos);

    void update(float dt);

    void draw(sf::RenderWindow& window);

    int consumeSpeedIncrease();

    void reset();

private:
    int score = 0;

    int speedLevel = 0;
    const int SPEED_STEP = 1500;

    const float NEAR_MISS_DURATION = 1.5f;
    float nearMissTimer = 0.0f;
    sf::Text nearMissText;

    sf::Text scoreText;

    const sf::Font* fontPtr = nullptr;
};
