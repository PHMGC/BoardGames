#pragma once

#include <iostream>

#include "Scene.hpp"
#include "TextComponent.hpp"

class PlayerContainer {
public:
    TextComponent label;
    sf::RectangleShape box;
    sf::Text text;
    std::string input;
	size_t MAX_INPUT_SIZE = 23;
	sf::Sprite enter;
	sf::Texture enterT;
	sf::Sprite checkmark;
	sf::Texture checkmarkT;
	sf::Sprite cross;
	sf::Texture crossT;

	PlayerContainer(const std::string& labelText, const sf::Font& font, const unsigned int fontSize, const sf::Vector2f pos)
	: label(labelText, font, fontSize, {0, 0}, {2, 4}),
		box({300, 45}),
		text(font, "Insira apelido", 15),
		enterT("../assets/enter.png"),
		checkmarkT("../assets/checkmark.png"),
		crossT("../assets/cross.png"),
		enter(enterT),
		checkmark(checkmarkT),
		cross(crossT)
	{
		// Configuração da caixa
		box.setPosition(pos);
		box.setFillColor(sf::Color(50, 50, 50, 200));
		box.setOutlineThickness(2);
		box.setOutlineColor(sf::Color::Black);

		// Configuração do label e do texto
		label.setPos(pos + sf::Vector2f(25, -40));
		text.setPosition(pos + sf::Vector2f(5, box.getSize().y / 2 - 10));

		// Inicialização do enter
		if (!enterT.loadFromFile("../assets/enter.png")) {
			throw std::runtime_error("Falha ao carregar a textura de 'entrar'");
		}
		enter.setTexture(enterT);
		enter.setPosition(pos + sf::Vector2f(0, 0));
		enter.setScale({0.5f, 0.5f});

		// Inicialização do yes
		if (!checkmarkT.loadFromFile("../assets/checkmark.png")) {
			throw std::runtime_error("Falha ao carregar a textura de 'checkmark'");
		}
		checkmark.setTexture(checkmarkT);
		checkmark.setPosition(pos + sf::Vector2f(0, 0));
		checkmark.scale({0.5f, 0.5f});

		// Inicialização do no
		if (!crossT.loadFromFile("../assets/cross.png")) {
			throw std::runtime_error("Falha ao carregar a textura de 'no'");
		}
		cross.setTexture(crossT);
		cross.setPosition(pos + sf::Vector2f(0, 0));
		cross.setScale({0.5f, 0.5f});
	}


	void updateInput(char typedChar) {
    	typedChar = std::toupper(typedChar);
    	if (typedChar == '\b' && !input.empty()) {
    		input.pop_back();
    	} else if (std::isprint(typedChar)) {
    		if (input.size() < MAX_INPUT_SIZE) {
    			input += typedChar;
    		}
    	}
    	text.setString(input);
    }

	sf::FloatRect getHitbox() const {
	    return box.getGlobalBounds();
    }

	void draw(sf::RenderWindow& window) {
	    window.draw(box);
    	label.draw(window);
    	window.draw(text);
    	window.draw(enter);
    	window.draw(checkmark);
    	window.draw(cross);
    }
};

class LoginScene final : public Scene {
	TextComponent title;
	PlayerContainer player1;
	PlayerContainer player2;
	TextComponent next;
	TextComponent back;

	int toggle_aux = 1;
	public:
	LoginScene(sf::RenderWindow& window, SceneManager* scene_manager, const std::string& font_path, const std::string& background_path)
	: Scene(window, scene_manager, font_path, background_path),
	title("LOGIN", font, 65, {500, 100},  {4, 8}),
	player1("Jogador 1", font, 30, {420, 290}),
	player2("Jogador 2", font, 30, {420, 390}),
	next("CONTINUAR", font, 25, {540, 540},  {2, 4}),
	back("VOLTAR", font, 25, {575, 590},  {2, 4})
	{
		next.setColor(GRAY);
	}

	void handleEvents(const std::optional<sf::Event> event) override {
		auto mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		std::vector<std::pair<sf::FloatRect, int>> hitboxes = {
			{player1.getHitbox(),				    1},
			{player2.getHitbox(),					2},
			{back.getHitbox(), 3},
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


        if (const auto* keyEvent = event->getIf<sf::Event::TextEntered>()) {
            char typedChar = static_cast<char>(keyEvent->unicode);
            if (toggle_aux == 1) {
                player1.updateInput(typedChar);
            } else if (toggle_aux == 2) {
                player2.updateInput(typedChar);
            }
        }


		for (const auto& [hitbox, index] : hitboxes) {
			if (hitbox.contains(mousePosition)) {
				toggle_aux = index;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					handleAction(index);
			}
		}

		player1.box.setOutlineColor(toggle_aux == 1 ? RED : BLACK);
		player2.box.setOutlineColor(toggle_aux == 2 ? RED : BLACK);
		back.setColor(toggle_aux == 3 ? RED : YELLOW);
	}

	void handleAction(int index);

	void draw() override {
		window.clear();

		window.draw(backgroundSprite);
		title.draw(window);
		player1.draw(window);
		player2.draw(window);
		next.draw(window);
		back.draw(window);

		window.display();
	};
};
