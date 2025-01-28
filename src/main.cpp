#include <SFML/Graphics.hpp>
#include "UI/SceneManager.hpp"
#include "GameManager.hpp"


int main() {
    GameManager gameManager;

    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Board Games", sf::Style::Titlebar | sf::Style::Close);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    SceneManager sceneManager(gameManager, window);

    while (window.isOpen()) {
        // Processar eventos
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            sceneManager.getCurrentScene().handleEvents(event);
        }
        sceneManager.draw();
    }

    return 0;
}
