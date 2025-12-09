#include "ScoreManager.h"

ScoreManager::ScoreManager() {
}

void ScoreManager::setFont(const sf::Font& f) {
    fontPtr = &f;

    scoreText.setFont(*fontPtr);
    scoreText.setCharacterSize(32);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20.f, 20.f);

    nearMissText.setFont(*fontPtr);
    nearMissText.setCharacterSize(40);
    nearMissText.setFillColor(sf::Color::Yellow);
    nearMissText.setStyle(sf::Text::Bold);
    nearMissText.setString("");
    nearMissText.setPosition(300.f, 150.f);
}

void ScoreManager::addScore(int s) {
    score += s;
}

int ScoreManager::getScore() const {
    return score;
}

void ScoreManager::triggerNearMiss(const sf::Vector2f& pos) {
    addScore(200);
    if (fontPtr) {
        nearMissText.setString("NEAR MISS! +200");
        nearMissText.setPosition(pos.x - 60.f, pos.y - 80.f);
        nearMissTimer = NEAR_MISS_DURATION;
    }
}

void ScoreManager::update(float dt) {
    if (nearMissTimer > 0.0f) {
        nearMissTimer -= dt;
        if (nearMissTimer <= 0.0f) {
            nearMissTimer = 0.0f;
            nearMissText.setString("");
        }
    }

    scoreText.setString("Score: " + std::to_string(score));
}

void ScoreManager::draw(sf::RenderWindow& window) {
    window.draw(scoreText);
    if (nearMissTimer > 0.0f) window.draw(nearMissText);
}

int ScoreManager::consumeSpeedIncrease() {
    int newLevel = score / SPEED_STEP;
    if (newLevel > speedLevel) {
        int levelsToAdd = newLevel - speedLevel;
        speedLevel = newLevel;
        return levelsToAdd;
    }
    return 0;
}

void ScoreManager::reset() {
    score = 0;
    speedLevel = 0;
    nearMissTimer = 0.0f;
    nearMissText.setString("");
    scoreText.setString("Score: 0");
}
