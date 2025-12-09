#include "Track.h"

Track::Track(int width, int windowWidth, int windowHeight, sf::Texture& grassTex)
    : trackWidth(width), grassTexture(grassTex)
{
    trackLeft = (windowWidth - trackWidth) / 2;
    trackRight = trackLeft + trackWidth;

    int grassWidth = grassTexture.getSize().x;
    int grassHeight = grassTexture.getSize().y;

    for (int y = 0; y < windowHeight; y += grassHeight)
        for (int x = 0; x < trackLeft; x += grassWidth)
        {
            sf::Sprite s(grassTexture);
            s.setPosition(static_cast<float>(x), static_cast<float>(y));
            leftGrassSprites.push_back(s);
        }

    for (int y = 0; y < windowHeight; y += grassHeight)
        for (int x = trackRight; x < windowWidth; x += grassWidth)
        {
            sf::Sprite s(grassTexture);
            s.setPosition(static_cast<float>(x), static_cast<float>(y));
            rightGrassSprites.push_back(s);
        }

    for (int i = 1; i < 3; ++i) {
        sf::RectangleShape line(sf::Vector2f(5.f, static_cast<float>(windowHeight)));
        float lineX = static_cast<float>(trackLeft) + static_cast<float>(i) * static_cast<float>(trackWidth) / 3.f - 2.5f;
        line.setPosition(lineX, 0.f);
        line.setFillColor(sf::Color::White);
        laneLines.push_back(line);
    }
}

void Track::draw(sf::RenderWindow& window) {
    for (auto& s : leftGrassSprites) window.draw(s);
    for (auto& s : rightGrassSprites) window.draw(s);

    sf::RectangleShape trackRect(sf::Vector2f(static_cast<float>(trackWidth), 600.f));
    trackRect.setPosition(static_cast<float>(trackLeft), 0.f);
    trackRect.setFillColor(sf::Color(100, 100, 100));
    window.draw(trackRect);

    for (auto& line : laneLines) window.draw(line);
}

std::vector<float> Track::getLanes() const {
    return {
        static_cast<float>(trackLeft) + static_cast<float>(trackWidth) / 6.f - 25.f,
        static_cast<float>(trackLeft) + static_cast<float>(trackWidth) / 2.f - 25.f,
        static_cast<float>(trackRight) - static_cast<float>(trackWidth) / 6.f - 25.f
    };
}

int Track::getLeft() const { return trackLeft; }
int Track::getRight() const { return trackRight; }
