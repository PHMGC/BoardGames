//#include <SFML/Graphics.hpp>
#include "UI/SceneManager.hpp"
#include "GameManager.hpp"


// sf::Vector2u adjustSize(sf::Vector2u newSize ,sf::Vector2u &lastSize, float targetAspectRatio) {
//     float newAspectRatio = static_cast<float>(newSize.x) / newSize.y;
//     // Permite movimentos APENAS nas diagonais
//     if (newSize.x == lastSize.x || newSize.y == lastSize.y) {
//         return lastSize;
//     }
//
//     if (newAspectRatio > targetAspectRatio) {
//         // Nova largura baseada na altura
//         newSize.x = static_cast<unsigned int>(newSize.y * targetAspectRatio);
//     } else {
//         // Nova altura baseada na largura
//         newSize.y = static_cast<unsigned int>(newSize.x / targetAspectRatio);
//     }
//     lastSize = newSize;
//     return newSize;
// }

int main() {
    // // Proporção fixa 16:9
    // constexpr float aspectRatio = 16.0f / 9.0f;
    //
    // sf::RenderWindow window(sf::VideoMode({1280, 720}), "Board Games", sf::Style::Titlebar | sf::Style::Close);
    //
    // window.setVerticalSyncEnabled(true);
    // window.setFramerateLimit(144);
    //
    // SceneManager scene_manager(window);
    //
    // sf::Vector2u lastSize = window.getSize();
    //
    // while (window.isOpen()) {
    //     // Processar eventos
    //     while (const std::optional event = window.pollEvent()) {
    //         if (event->is<sf::Event::Closed>()) {
    //             window.close();
    //         }
    //         if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
    //             if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
    //                 window.close();
    //             }
    //         }
    //
    //         // if (const auto resized = event->getIf<sf::Event::Resized>()) {
    //         //     window.setSize(adjustSize(resized->size, lastSize, aspectRatio));
    //         // }
    //
    //         scene_manager.getCurrentScene().handleEvents(event);
    //     }
    //     scene_manager.getCurrentScene().draw();
    // }

    GameManager game_manager;
    game_manager.run();


    return 0;
}
