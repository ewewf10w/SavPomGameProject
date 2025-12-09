#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Game.h"

class MainMenu {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text titleText;

    Button playButton;
    Button exitButton;

    bool fontLoaded;
    bool mousePressed;

public:
    MainMenu(sf::RenderWindow& win);
    ~MainMenu() = default;

    bool loadFont(const std::string& fontPath);
    

private:
    void handleEvents();
    void update();
    void render();
    void reset();
};