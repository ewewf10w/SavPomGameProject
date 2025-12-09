#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class MainMenu {
private:
    sf::Text logo;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    Button* playButton;
    Button* exitButton;

public:
    MainMenu();
    ~MainMenu();

    void update(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    bool playClicked() const;
    bool exitClicked() const;
};
