#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow& win)
    : window(win),
    fontLoaded(false),
    mousePressed(false),
    playButton(sf::Vector2f(300, 250), sf::Vector2f(200, 60), "Play", font),
    exitButton(sf::Vector2f(300, 350), sf::Vector2f(200, 60), "Exit", font) {

    reset();
}

bool MainMenu::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font for MainMenu: " << fontPath << std::endl;
        fontLoaded = false;
        return false;
    }

    fontLoaded = true;

    // Настройка заголовка
    titleText.setFont(font);
    titleText.setString("SPRace");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f,
        titleBounds.top + titleBounds.height / 2.0f);
    titleText.setPosition(window.getSize().x / 2.0f, 150.0f);

    // Обновляем кнопки с загруженным шрифтом
    playButton = Button(sf::Vector2f(300, 250), sf::Vector2f(200, 60), "Play", font);
    exitButton = Button(sf::Vector2f(300, 350), sf::Vector2f(200, 60), "Exit", font);

    return true;
}

void MainMenu::run() {
    if (!fontLoaded) {
        std::cerr << "Font not loaded! Cannot run MainMenu." << std::endl;
        return;
    }

    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void MainMenu::handleEvents() {
    sf::Event event;
    mousePressed = false;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                mousePressed = true;
            }
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}

void MainMenu::update() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    playButton.update(mousePos);
    exitButton.update(mousePos);

    if (playButton.isClicked(mousePos, mousePressed)) {
        // Запускаем игру
        Game game(window.getSize().x, window.getSize().y);
        game.run();
        reset(); // Возвращаемся в меню после окончания игры
    }

    if (exitButton.isClicked(mousePos, mousePressed)) {
        window.close();
    }
}

void MainMenu::render() {
    window.clear(sf::Color(30, 30, 50)); // Тёмно-синий фон

    if (fontLoaded) {
        window.draw(titleText);
        playButton.draw(window);
        exitButton.draw(window);
    }

    window.display();
}

void MainMenu::reset() {
    // Сброс состояния меню (если нужно)
    mousePressed = false;
}