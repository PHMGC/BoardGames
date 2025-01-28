#pragma once

#include <iostream>

#include "Scene.hpp"
#include "TextComponent.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class SignInScene final : public Scene {
	InputContainer player1;
	InputContainer player2;
	TextComponent next;
	TextComponent back;

	int currentIndex = 0;
	int maxIndex = 3;
	public:
	SignInScene(GameManager& gameManager, sf::RenderWindow& window, SceneManager* sceneManager, const std::string& font_path)
	:	Scene(gameManager, window, sceneManager, font_path),
		player1("Jogador 1", "Insira Apelido", font, 30, {485, 375}),
		player2("Jogador 2", "Insira Apelido", font, 30, {485, 480}),
		next("Continuar",	 				   font, 25, {530, 575}, {2, 4}),
		back("Voltar",		 				   font, 25, {570, 625}, {2, 4})
	{
		next.setEnabled(false);
	}

	void handleEvents(const std::optional<sf::Event> event) override {
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
				currentIndex--;
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
				currentIndex++;
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
				handleAction();
		}
		maxIndex = next.isEnabled() ? 3 : 2;
		currentIndex = std::clamp(currentIndex, 0, maxIndex);

		next.setEnabled(player1.hasInput() && player2.hasInput());

        if (const auto* keyEvent = event->getIf<sf::Event::TextEntered>()) {
            char typedChar = static_cast<char>(keyEvent->unicode);
        	if (currentIndex == 0) {
        		player1.setTyping(true);
        		player1.updateInput(typedChar);
        		player2.setTyping(false);
        	}
        	if (currentIndex == 1) {
        		player2.setTyping(true);
        		player2.updateInput(typedChar);
        		player1.setTyping(false);
        	}
        }

		player1.setHover(currentIndex == 0);
		player2.setHover(currentIndex == 1);
		next.isEnabled() ? next.setHover(currentIndex == 2) : next.setHover(false);
		back.setHover(currentIndex == maxIndex);
	}

	bool validatePlayerInput(InputContainer& container);
	void handleAction();

	void draw() override {
		player1.draw(window);
		player2.draw(window);
		next.draw(window);
		back.draw(window);
	};
};