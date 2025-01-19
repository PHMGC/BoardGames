#pragma once

#include "Scene.hpp"
#include "TextComponent.hpp"

class LoginScene final : public Scene {
	TextComponent title;
	TextComponent player1Text;
	sf::RectangleShape player1Box;
	TextComponent player2Text;
	sf::RectangleShape player2Box;
	TextComponent back;

	int toggle_aux = 1;
	public:
	LoginScene(sf::RenderWindow& window, SceneManager* scene_manager, const std::string& font_path, const std::string& background_path)
	: Scene(window, scene_manager, font_path, background_path),
	title("LOGIN", font, 65, {500, 100},  {4, 8}),
	player1Text("Player One", font, 30, {510, 240},  {2, 4}),
	player1Box({300,45}),
	player2Text("Player Two", font, 30, {510, 380},  {2, 4}),
	player2Box({300,45}),
	back("VOLTAR", font, 30, {560, 560},  {2, 4})
	{
		player1Box.setFillColor(sf::Color(50, 50, 50, 200));
		player1Box.setPosition({490, 290});
		player1Box.setOutlineThickness(2);
		player1Box.setOutlineColor(sf::Color(RED));

		player2Box.setFillColor(sf::Color(50, 50, 50, 200));
		player2Box.setPosition({490, 430});
		player2Box.setOutlineThickness(2);
		player2Box.setOutlineColor(sf::Color(BLACK));
	}

	void handleEvents(const std::optional<sf::Event> event) override {
		auto mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
		auto hitBoxes = {
			std::make_pair(&back, 1),
		};

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
				toggle_aux = (toggle_aux > 1) ? toggle_aux - 1 : hitBoxes.size();
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
				toggle_aux = (toggle_aux < hitBoxes.size()) ? toggle_aux + 1 : 1;
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
				handleAction(toggle_aux);
		}

		for (const auto& [textComponent, index] : hitBoxes) {
			if (textComponent->getText().getGlobalBounds().contains(mousePosition)) {
				toggle_aux = index;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					handleAction(index);
			}
		}

		back.getText().setFillColor(toggle_aux == 1 ? RED : YELLOW);
	}

	void handleAction(int index);

	void draw() override {
		window.clear();
		window.draw(backgroundSprite);
		title.draw(window);
		player1Text.draw(window);
		player2Text.draw(window);
		window.draw(player1Box);
		window.draw(player2Box);
		back.draw(window);
		window.display();
	};
};
