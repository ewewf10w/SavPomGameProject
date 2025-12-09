#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SPRACE");
    window.setFramerateLimit(60);

    MainMenu menu;

    bool inGame = false;

    Game* game = nullptr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        if (!inGame) {
            menu.update(window);
            menu.draw(window);

            if (menu.playClicked()) {
                inGame = true;
                game = new Game(window);
            }
            if (menu.exitClicked()) {
                window.close();
            }
        }
        else {
            game->run();
        }

        window.display();
    }

    if (game) delete game;

    return 0;
}
