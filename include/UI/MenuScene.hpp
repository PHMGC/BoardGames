#pragma once

#include "Scene.hpp"
#include "TextComponent.hpp"
#include "ParallaxComponent.hpp"

class MenuScene final : public Scene {
    TextComponent play;
    TextComponent signup;
    TextComponent leaderboard;
    TextComponent quit;

    int currentIndex = 0;

public:
    MenuScene(GameManager& gameManager, sf::RenderWindow& window, SceneManager* sceneManager, const std::string& font_path)
    : Scene(gameManager, window, sceneManager, font_path),
        play  ("Jogar",       font, 38, {550, 350}, {2, 4}),
        signup("Cadastro",    font, 38, {485, 425}, {2, 4}),
        leaderboard("Placar", font, 32, {550, 500}, {2, 4}),
        quit("Sair",          font, 32, {570, 575}, {2, 4})
    {}

    void handleEvents(const std::optional<sf::Event> event) override {
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                currentIndex--;
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                currentIndex++;
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
                handleAction(currentIndex);
        }
        currentIndex = std::clamp(currentIndex, 0, 3);

        play.setColor(currentIndex == 0 ? RED : YELLOW);
        signup.setColor(currentIndex == 1 ? RED : YELLOW);
        leaderboard.setColor(currentIndex == 2 ? RED : YELLOW);
        quit.setColor(currentIndex == 3 ? RED : YELLOW);
    }

    void handleAction(int index);

    void draw() override {
        play.draw(window);
        signup.draw(window);
        leaderboard.draw(window);
        quit.draw(window);
    }
};
