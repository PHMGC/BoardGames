#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>

#include "GameManager.hpp"

class SceneManager;

class Scene {
protected:
	GameManager& gameManager;

	sf::RenderWindow& window;
	SceneManager* sceneManager;
	sf::Font font;

public:
	Scene(GameManager& gameManager, sf::RenderWindow& window, SceneManager* sceneManager, const std::string& font_path)
		: gameManager(gameManager), window(window), sceneManager(sceneManager), font(font_path) {
		if (!font.openFromFile(font_path)) {
			throw std::invalid_argument("Erro ao carregar a fonte!");
		}
	}

	virtual ~Scene() = default;
	virtual void handleEvents(std::optional<sf::Event> event) = 0;
	virtual void draw() = 0;
};
