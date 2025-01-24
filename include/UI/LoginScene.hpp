#pragma once

#include <iostream>

#include "Scene.hpp"
#include "TextComponent.hpp"

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

struct ImageContainer {
	sf::Texture texture;
	sf::Sprite sprite;

	explicit ImageContainer(const std::string& texture_path) : texture(texture_path), sprite(texture) {
		if (!texture.loadFromFile(texture_path)) {
			throw std::runtime_error("Failed to load " + texture_path);
		}
		sprite.setTexture(texture);
	}
};

struct PlayerContainer {
    TextComponent label;
    sf::RectangleShape box;
    sf::Text text;
    std::string nicknameInput;
    std::string nameInput;
    static constexpr size_t MAX_INPUT_SIZE = 23;
    ImageContainer enter;
    ImageContainer checkmark;
    ImageContainer cross;
	bool isHover = false;
    bool isTyping = false;
    bool isNicknameInput = true;

    PlayerContainer(const std::string& labelText, const sf::Font& font, const unsigned int fontSize, const sf::Vector2f pos)
        : label(labelText, font, fontSize, {0, 0}, {2, 4}),
          box({300, 45}),
          text(font, "Insira apelido", fontSize / 2),
          enter("../assets/enter.png"),
          checkmark("../assets/checkmark.png"),
          cross("../assets/cross.png") {
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
        label.setPos(pos + sf::Vector2f(25, -40));
        text.setPosition(pos + sf::Vector2f(5, box.getSize().y / 2 - 10));
    }

    void configureIcons(const sf::Vector2f& pos) {
        enter.sprite.setPosition(pos + sf::Vector2f(310, 2));
        enter.sprite.setScale({0.3f, 0.3f});

        checkmark.sprite.setPosition(pos + sf::Vector2f(310, 2));
        checkmark.sprite.setScale({0.15f, 0.15f});

        cross.sprite.setPosition(pos + sf::Vector2f(355, 2));
        cross.sprite.setScale({0.15f, 0.15f});
    }

    void updateInput(char typedChar) {
        if (!isTyping) return;
    	std::string& input = isNicknameInput ? nicknameInput : nameInput;
        typedChar = std::toupper(typedChar);
        if (typedChar == '\b' && !input.empty()) {
            input.pop_back();
        } else if (std::isprint(typedChar) && input.size() < MAX_INPUT_SIZE) {
            input += typedChar;
        }
    }

    void setInput(bool isNickname) {
        isNicknameInput = isNickname;
    }

	void setTyping(bool typing) {
    	isTyping = typing;
    }

    bool hasInput(bool isNickname) const {
        return isNickname ? !nicknameInput.empty() : !nameInput.empty();
    }

    void setHover(bool hover) {
    	isHover = hover;
    	box.setOutlineColor(hover ? RED : BLACK);
    }

	void updateText() {
    	std::string& input = isNicknameInput ? nicknameInput : nameInput;
    	std::string placeholder = isNicknameInput ? "Insira apelido" : "Insira nome";
    	text.setString(input);
    	if (!isTyping) {
    		if (input.empty()) {
    			text.setString(placeholder);
    		}
    	}
    }


    void update(sf::RenderWindow& window) {
        window.draw(box);
        label.draw(window);

    	updateText();
        window.draw(text);
    	if (isNicknameInput) {
	        window.draw(enter.sprite);
    	} else {
	        window.draw(checkmark.sprite);
    		window.draw(cross.sprite);
    	}
    }
};


class LoginScene final : public Scene {
	TextComponent title;
	PlayerContainer player1;
	PlayerContainer player2;
	TextComponent next;
	TextComponent back;

	int currentIndex = 0;
	int maxIndex = 3;
	public:
	LoginScene(sf::RenderWindow& window, SceneManager* scene_manager, const std::string& font_path, const std::string& background_path)
	:	Scene(window, scene_manager, font_path, background_path),
		title("LOGIN", font, 65, {500, 100},  {4, 8}),
		player1("Jogador 1", font, 30, {420, 290}),
		player2("Jogador 2", font, 30, {420, 390}),
		next("CONTINUAR", font, 25, {540, 540},  {2, 4}),
		back("VOLTAR", font, 25, {575, 590},  {2, 4})
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
		currentIndex = std::min(currentIndex, maxIndex);
		currentIndex = std::max(0, currentIndex);

		next.setEnabled(player1.hasInput(true) && player2.hasInput(true));

        if (const auto* keyEvent = event->getIf<sf::Event::TextEntered>()) {
            char typedChar = static_cast<char>(keyEvent->unicode);
        	if (currentIndex == 0) {
        		player1.updateInput(typedChar);
        	}
        	if (currentIndex == 1) {
        		player2.updateInput(typedChar);
        	}
        }

		player1.setHover(currentIndex == 0);
		player2.setHover(currentIndex == 1);
		next.isEnabled() ? next.setHover(currentIndex == 2) : next.setHover(false);
		back.setHover(currentIndex == maxIndex);
	}

	void handleAction();

	void update() override {
		window.clear();

		window.draw(backgroundSprite);
		title.draw(window);
		player1.update(window);
		player2.update(window);
		next.draw(window);
		back.draw(window);

		window.display();
	};
};