#pragma once

#include <iostream>

#include "Scene.hpp"
#include "TextComponent.hpp"
#include "InputContainer.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class SignUpScene final : public Scene {
	InputContainer playerNickname;
	InputContainer playerName;
	TextComponent signup;
	TextComponent back;

	bool isSignUpSucessfull = false;

	int currentIndex = 0;
	int maxIndex = 3;
	public:
	SignUpScene(GameManager& gameManager, sf::RenderWindow& window, SceneManager* sceneManager, const std::string& font_path)
	:	Scene(gameManager, window, sceneManager, font_path),
		playerNickname("Apelido", "Insira Apelido", font, 30, {485, 375}),
		playerName	  ("Nome", "Insira Nome",		font, 30, {485, 480}),
		signup		  ("Cadastrar",		 			font, 25, {530, 575}, {2, 4}),
		back		  ("Voltar",			 		font, 25, {570, 625}, {2, 4})
	{
		signup.setEnabled(false);
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
		maxIndex = signup.isEnabled() ? 3 : 2;
		currentIndex = std::clamp(currentIndex, 0, maxIndex);

		signup.setEnabled(playerNickname.hasInput() && playerName.hasInput());

        if (const auto* keyEvent = event->getIf<sf::Event::TextEntered>()) {
            char typedChar = static_cast<char>(keyEvent->unicode);
        	if (currentIndex == 0) {
        		playerNickname.setTyping(true);
        		playerNickname.updateInput(typedChar);
        		playerName.setTyping(false);
        		isSignUpSucessfull = false;
        	}
        	if (currentIndex == 1) {
        		playerName.setTyping(true);
        		playerName.updateInput(typedChar);
        		playerNickname.setTyping(false);
        		isSignUpSucessfull = false;
        	}
        }

		playerNickname.setHover(currentIndex == 0);
		playerName.setHover(currentIndex == 1);
		signup.isEnabled() ? signup.setHover(currentIndex == 2) : signup.setHover(false);
		back.setHover(currentIndex == maxIndex);

		if (isSignUpSucessfull) {
			signup.setText("Sucesso!");
			signup.setPos({550, 575});
		}
		else {
			signup.setText("Cadastrar");
			signup.resetPos();
		}
	}

	bool validateInput(InputContainer& container);
	void handleAction();

	void draw() override {
		playerNickname.draw(window);
		playerName.draw(window);
		signup.draw(window);
		back.draw(window);
	};
};