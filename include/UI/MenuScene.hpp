#pragma once

#include "Scene.hpp"
#include "TextComponent.hpp"

class MenuScene final : public Scene {
    TextComponent title1;
    TextComponent title2;
    TextComponent play;
    TextComponent leaderboard;
    TextComponent quit;

    int toggle_aux = 1;

public:
    MenuScene(sf::RenderWindow& window, SceneManager* scene_manager, const std::string& font_path, const std::string& background_path)
    : Scene(window, scene_manager, font_path, background_path),
        title1("BOARD",           font, 65, {460, 80},  {4, 8}),
        title2("GAMES",           font, 60, {559, 155}, {4, 8}),
        play  ("PLAY",            font, 38, {575, 300}, {2, 4}),
        leaderboard("LEADERBOARD",font, 32, {490, 404}, {2, 4}),
        quit("QUIT",              font, 32, {590, 506}, {2, 4})
    {
        title2.rotate(sf::degrees(-7));
    }

    void handleEvents(const std::optional<sf::Event> event) override {
		std::vector<std::pair<sf::FloatRect, int>> hitboxes = {
            {play.getHitbox(),        1},
            {leaderboard.getHitbox(), 2},
            {quit.getHitbox(),        3}
        };

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                toggle_aux--;
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                toggle_aux++;
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
                handleAction(toggle_aux);
        }
        toggle_aux = std::clamp(toggle_aux, 1, static_cast<int>(hitboxes.size()));

        play.setColor(toggle_aux == 1 ? RED : YELLOW);
        leaderboard.setColor(toggle_aux == 2 ? RED : YELLOW);
        quit.setColor(toggle_aux == 3 ? RED : YELLOW);
    }

    void handleAction(int index);

    void update() override {
        window.clear();

        window.draw(backgroundSprite);

        title1.draw(window);
        title2.draw(window);
        play.draw(window);
        leaderboard.draw(window);
        quit.draw(window);

        window.display();
    }
};
