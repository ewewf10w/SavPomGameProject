#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Track {
private:
    int trackLeft, trackRight, trackWidth;
    sf::Texture& grassTexture;

    std::vector<sf::Sprite> grassSprites;
    std::vector<sf::RectangleShape> laneLines;
    sf::RectangleShape roadRect;

public:
    Track(int width, int windowWidth, int windowHeight, sf::Texture& grassTex);

    void draw(sf::RenderWindow& window);
    std::vector<float> getLanes() const;

    int getLeft() const { return trackLeft; }
    int getRight() const { return trackRight; }
};