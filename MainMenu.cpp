#include "MainMenu.h"
#include <iostream>
#include <SFML/Graphics.hpp>

MainMenu::MainMenu() {
    if (!font.loadFromFile("fonts/race-master.ttf")) {
        std::cerr << "Failed to load font!\n";
    }

    logo.setFont(font);
    logo.setString("SPRACE");
    logo.setCharacterSize(72); 
    logo.setFillColor(sf::Color::White);
    logo.setStyle(sf::Text::Bold);

    sf::FloatRect bounds = logo.getLocalBounds();
    logo.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    logo.setPosition(400.f, 100.f);

    playButton = new Button({ 200.f, 50.f }, { 300.f, 300.f }, font, "PLAY",
        sf::Color(70, 70, 70), sf::Color(150, 150, 150), sf::Color(20, 20, 20));

    exitButton = new Button({ 200.f, 50.f }, { 300.f, 400.f }, font, "EXIT",
        sf::Color(70, 70, 70), sf::Color(150, 150, 150), sf::Color(20, 20, 20));

    if (!backgroundTexture.loadFromFile("images/menu-bg.jpg")) {
        std::cout << "Не удалось загрузить фон!" << std::endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(
            800.f / backgroundTexture.getSize().x,
            600.f / backgroundTexture.getSize().y
        );
    }
}

MainMenu::~MainMenu() {
    delete playButton;
    delete exitButton;
}

void MainMenu::update(const sf::RenderWindow& window) {
    playButton->update(window);
    exitButton->update(window);
}

void MainMenu::draw(sf::RenderWindow& window) {
    if (backgroundTexture.getSize().x > 0)
        window.draw(backgroundSprite);
    window.draw(logo);
    playButton->draw(window);
    exitButton->draw(window);
}

bool MainMenu::playClicked() const {
    return playButton->isPressed();
}

bool MainMenu::exitClicked() const {
    return exitButton->isPressed();
}
