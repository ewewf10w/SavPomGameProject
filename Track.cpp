#include "Track.h"

Track::Track(int width, int windowWidth, int windowHeight, sf::Texture& grassTex)
    : trackWidth(width), grassTexture(grassTex)
{
    trackLeft = (windowWidth - trackWidth) / 2;
    trackRight = trackLeft + trackWidth;

    const int grassW = grassTexture.getSize().x;
    const int grassH = grassTexture.getSize().y;

    auto fillGrass = [&](int startX, int endX)
        {
            for (int y = 0; y < windowHeight; y += grassH)
                for (int x = startX; x < endX; x += grassW)
                {
                    sf::Sprite s(grassTexture);
                    s.setPosition((float)x, (float)y);
                    grassSprites.push_back(s);
                }
        };

    fillGrass(0, trackLeft);
    fillGrass(trackRight, windowWidth);

    roadRect.setSize({ (float)trackWidth, (float)windowHeight });
    roadRect.setPosition((float)trackLeft, 0);
    roadRect.setFillColor({ 100, 100, 100 });

    for (int i = 1; i < 3; ++i) {
        float x = trackLeft + (float)i * trackWidth / 3.f - 2.5f;

        sf::RectangleShape line({ 5.f, (float)windowHeight });
        line.setPosition(x, 0);
        line.setFillColor(sf::Color::White);

        laneLines.push_back(line);
    }
}

void Track::draw(sf::RenderWindow& window)
{
    for (auto& s : grassSprites) window.draw(s);
    window.draw(roadRect);
    for (auto& ln : laneLines) window.draw(ln);
}

std::vector<float> Track::getLanes() const
{
    constexpr float CAR_OFFSET = 25.f;

    return {
        trackLeft + trackWidth / 6.f - CAR_OFFSET,
        trackLeft + trackWidth / 2.f - CAR_OFFSET,
        trackRight - trackWidth / 6.f - CAR_OFFSET
    };
}