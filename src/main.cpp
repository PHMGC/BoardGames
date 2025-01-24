#include <SFML/Graphics.hpp>
#include "UI/SceneManager.hpp"
#include "GameManager.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Board Games", sf::Style::Titlebar | sf::Style::Close);

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    SceneManager scene_manager(window);

    while (window.isOpen()) {
        // Processar eventos
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            scene_manager.getCurrentScene().handleEvents(event);
        }
        scene_manager.getCurrentScene().update();
    }

    // GameManager game_manager;
    // game_manager.run();


    return 0;
}
