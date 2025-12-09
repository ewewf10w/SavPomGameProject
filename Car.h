#pragma once
#include <SFML/Graphics.hpp>

class Car {
protected:
    sf::Sprite sprite;
    float speed;

public:
    Car(sf::Texture& texture, float x, float y, float s);
    virtual void update();
    void move(float dx, float dy);
    sf::FloatRect getBounds() const;
    sf::Sprite& getSprite();
    virtual ~Car() = default;
};

class PlayerCar : public Car {
public:
    PlayerCar(sf::Texture& texture, float x, float y, float s);
    void handleInput(float leftBound, float rightBound, float topBound, float bottomBound);
};

class EnemyCar : public Car {
public:
    bool wasNearMiss = false;
    bool overtaken = false;
    float lastY = 0.0f;        
    EnemyCar(sf::Texture& texture, float x, float y, float s);
    bool getWasNearMiss() const { return wasNearMiss; }
    void setWasNearMiss(bool v) { wasNearMiss = v; }

    void addSpeed(float delta) { speed += delta; }
};