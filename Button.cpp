#include "Button.h"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position,
    const sf::Font& font, const std::string& textStr,
    const sf::Color& idle, const sf::Color& hover, const sf::Color& active)
    : idleColor(idle), hoverColor(hover), activeColor(active)
{
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(idleColor);

    text.setFont(font);
    text.setString(textStr);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f);
    text.setPosition(position.x + size.x / 2.f, position.y + size.y / 2.f);
}

void Button::update(const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect bounds = shape.getGlobalBounds();
    isHovered = bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (isHovered) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            shape.setFillColor(activeColor);
        else
            shape.setFillColor(hoverColor);
    }
    else {
        shape.setFillColor(idleColor);
    }
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

bool Button::isPressed() const {
    return isHovered && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
