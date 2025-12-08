#include "Car.h"

Car::Car(sf::Texture& texture, float x, float y, float s) : speed(s) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Car::update() {
    sprite.move(0, speed);
}

void Car::move(float dx, float dy) {
    sprite.move(dx, dy);
}

sf::FloatRect Car::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Sprite& Car::getSprite() {
    return sprite;
}

// --- PlayerCar ---
PlayerCar::PlayerCar(sf::Texture& texture, float x, float y, float s) : Car(texture, x, y, s) {}

void PlayerCar::handleInput(float leftBound, float rightBound, float topBound, float bottomBound) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x > leftBound)
        move(-speed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sprite.getPosition().x + sprite.getGlobalBounds().width < rightBound)
        move(speed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sprite.getPosition().y > topBound)
        move(0, -speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sprite.getPosition().y + sprite.getGlobalBounds().height < bottomBound)
        move(0, speed);
}

// --- EnemyCar ---
EnemyCar::EnemyCar(sf::Texture& texture, float x, float y, float s) : Car(texture, x, y, s) {}
