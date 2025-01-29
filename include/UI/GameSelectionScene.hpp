#pragma once

#include "Scene.hpp"
#include "BillboardComponent.hpp"
#include "TextComponent.hpp"


class GameSelectionScene : public Scene {
	TextComponent back;
	TextComponent play;

	BillboardComponent billboards;
	bool hasInit = false;

	int gameIndex = 0;
	int buttonIndex = -1;

	sf::Clock clock;
	float lastAnimationTime = 0.0f;
	bool drawButtons = false;

	public:
	GameSelectionScene(GameManager& gameManager, sf::RenderWindow& window, SceneManager* sceneManager, const std::string& font_path)
	:	Scene(gameManager, window, sceneManager, font_path),
		back("Voltar",	   font, 25, {300, 625}, {2, 4}),
		play("Selecionar", font, 25, {800, 625}, {2, 4}),
		billboards("../assets/billboards.png")
	{}

	void init() {
		billboards.startVerticalAnimation();
		lastAnimationTime = clock.getElapsedTime().asSeconds();
	}

	void reset() {
		buttonIndex = -1;
	}

	void handleEvents(const std::optional<sf::Event> event) override {
		if (!hasInit) {
			init();
			hasInit = true;
		}
		//std::cout << clock.getElapsedTime().asMilliseconds() - lastAnimationTime << "\n";
		if (clock.getElapsedTime().asSeconds() - lastAnimationTime > 2) {
			drawButtons = true;
		}
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			if (clock.getElapsedTime().asSeconds() - lastAnimationTime < 2) return;
			if (keyPressed->scancode == sf::Keyboard::Scancode::Right) {
				if (gameIndex < 2) {
					lastAnimationTime = clock.getElapsedTime().asSeconds();
					gameIndex++;
					billboards.startHorizontalAnimation(false);
				}
			}
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Left) {
				if (gameIndex > 0) {
					lastAnimationTime = clock.getElapsedTime().asSeconds();
					gameIndex--;
					billboards.startHorizontalAnimation(true);
				}
			}
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Up) {
				buttonIndex--;
			}
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {
				buttonIndex++;
			}
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
				handleAction();
			}

			buttonIndex = std::clamp(buttonIndex, -1, 1);
		}

		back.setHover(buttonIndex == 0);
		play.setHover(buttonIndex == 1);

	}

	void handleAction();

	void draw() override {
		billboards.draw(window);
		if (drawButtons) {
			back.draw(window);
			play.draw(window);
		}
	}


};