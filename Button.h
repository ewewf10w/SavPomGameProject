#pragma once
#include <SFML/Graphics.hpp>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color idleColor;
    sf::Color hoverColor;
    bool isHovered;

public:
    Button(sf::Vector2f position, sf::Vector2f size,
        const std::string& btnText, const sf::Font& font,
        sf::Color idleColor = sf::Color(70, 70, 200),
        sf::Color hoverColor = sf::Color(100, 100, 255));

    void draw(sf::RenderWindow& window);
    void update(const sf::Vector2f& mousePos);
    bool isClicked(const sf::Vector2f& mousePos, bool mousePressed);
    void setText(const std::string& newText);
};