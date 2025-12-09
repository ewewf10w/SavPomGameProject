#include "MainMenu.h"

int main() {
    // Создаём окно для меню (можно сделать того же размера, что и игра)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Avoid Cars - Main Menu");
    window.setFramerateLimit(60);

    // Создаём меню
    MainMenu menu(window);

    // Загружаем шрифт (используем тот же, что и в игре)
    if (!menu.loadFont("fonts/race-master.ttf")) {
        // Если шрифт не загрузился, пробуем загрузить стандартный системный
        if (!menu.loadFont("arial.ttf")) {
            return -1; // Не удалось загрузить шрифт
        }
    }

    // Запускаем меню
    menu.run();

    return 0;
}