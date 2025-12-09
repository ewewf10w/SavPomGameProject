#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size,
    const std::string& btnText, const sf::Font& font,
    sf::Color idleColor, sf::Color hoverColor)
    : idleColor(idleColor), hoverColor(hoverColor), isHovered(false) {

    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(idleColor);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::White);

    text.setFont(font);
    text.setString(btnText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
    text.setPosition(position.x + size.x / 2.0f,
        position.y + size.y / 2.0f);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

void Button::update(const sf::Vector2f& mousePos) {
    isHovered = shape.getGlobalBounds().contains(mousePos);
    shape.setFillColor(isHovered ? hoverColor : idleColor);

}

bool Button::isClicked(const sf::Vector2f& mousePos, bool mousePressed) {
    return isHovered && mousePressed;
}

void Button::setText(const std::string& newText) {
    text.setString(newText);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
}