#pragma once

#include <iostream>

#include "Scene.hpp"
#include "TextComponent.hpp"

#include <SFML/Graphics.hpp>
#include <string>

struct InputContainer {
    TextComponent label;
    sf::RectangleShape box;
    sf::Text text;
    std::string input;
    static constexpr size_t MAX_INPUT_SIZE = 19;
    ImageComponent checkmark;
    ImageComponent cross;
	bool isHover = false;
    bool isTyping = false;
	bool isInputValid = true;
	bool hasEnteredInput = false;

	std::string default_placeholder;
	std::string placeholder;


    InputContainer(const std::string& labelText, const std::string& placeholderText, const sf::Font& font, const unsigned int fontSize, const sf::Vector2f pos)
        : label(labelText, font, fontSize, {0, 0}, {2, 4}),
		  box({300, 45}),
		  text(font, "Insira apelido", fontSize / 2),
          checkmark("../assets/checkmark.png"),
          cross("../assets/cross.png"),
          default_placeholder(placeholderText),
          placeholder(placeholderText) {
        configureBox(pos);
        configureLabelAndText(pos);
        configureIcons(pos);
    }

    void configureBox(const sf::Vector2f& pos) {
        box.setPosition(pos);
        box.setFillColor(sf::Color(50, 50, 50, 200));
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color::Black);
    }

    void configureLabelAndText(const sf::Vector2f& pos) {
        label.setPos(pos + sf::Vector2f(10, -40));
        text.setPosition(pos + sf::Vector2f(5, box.getSize().y / 2 - 7));
    }

    void configureIcons(const sf::Vector2f& pos) {
        checkmark.sprite.setPosition(pos + sf::Vector2f(310, 2));
        checkmark.sprite.setScale({0.15f, 0.15f});

        cross.sprite.setPosition(pos + sf::Vector2f(310, 2));
        cross.sprite.setScale({0.15f, 0.15f});
    }

	void updateInput(char typedChar) {
    	if (!isTyping) {
    		text.setString(input.empty() ? placeholder : input);
    		return;
    	}

    	setInvalidWarning(false, "");
    	if (typedChar == '\b' && !input.empty()) {
    		input.pop_back();
    	} else if (std::isprint(typedChar) && input.size() < MAX_INPUT_SIZE) {
    		input += typedChar;
    	}
    	text.setString(input.empty() ? placeholder : input);
    }


	void setInvalidWarning(bool enable, const std::string& warning) {
    	isInputValid = !enable;
    	placeholder = enable ? warning : default_placeholder;
    	text.setString(enable ? placeholder : (input.empty() ? placeholder : input));
    	if (enable) {
    		input.clear();
    	}
    }

	void setTyping(bool typing) {
    	isTyping = typing;
    	text.setString(input.empty() ? placeholder : input);
    }

    bool hasInput() const {
        return !input.empty();
    }

    void setHover(bool hover) {
    	isHover = hover;
    	box.setOutlineColor(hover ? RED : BLACK);
    }

	void setActive(bool active) {
	    setHover(active);
    	isTyping = active;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);
        label.draw(window);

        window.draw(text);
    	if (hasEnteredInput) {
    		if (isInputValid) {
    			window.draw(checkmark.sprite);
    		}
    		else{
    			window.draw(cross.sprite);
    		}
    	}
    }

	void reset() {
    	input.clear();
    	placeholder = default_placeholder;
    	setInvalidWarning(false, "");
    	hasEnteredInput = false;
    	text.setString(placeholder);
    }
};


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