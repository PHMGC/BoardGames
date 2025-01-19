#include "GameManager.hpp"
#include "UI/SceneManager.hpp"

int main()
{

    sf::RenderWindow game_window(sf::VideoMode({1280, 720}), "Board Games", sf::Style::Close);
    game_window.setVerticalSyncEnabled(true);
    game_window.setFramerateLimit(144);

    SceneManager scene_manager(game_window);

    try {
        while (game_window.isOpen()) {
            // Processar eventos
            while (const std::optional event = game_window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    game_window.close();
                }
                scene_manager.getCurrentScene().handleEvents(event);
            }
            scene_manager.getCurrentScene().draw();
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    //const GameManager manager;
    //manager.run();

    return 0;
}
