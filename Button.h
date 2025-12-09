#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

    bool isHovered = false;
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position,
        const sf::Font& font, const std::string& textStr,
        const sf::Color& idle, const sf::Color& hover, const sf::Color& active);

    void update(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    bool isPressed() const;
};
