#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <stdexcept>

class SceneManager;

class Scene {
protected:
	sf::RenderWindow& window;
	SceneManager* scene_manager;
	sf::Font font;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

public:
	Scene(sf::RenderWindow& window, SceneManager* scene_manager, const std::string& font_path, const std::string& background_path)
		: window(window), scene_manager(scene_manager), backgroundTexture(background_path), backgroundSprite(backgroundTexture) {
		if (!font.openFromFile(font_path)) {
			throw std::invalid_argument("Erro ao carregar a fonte! Verifique se ela está no caminho " + font_path);
		}

		if (!backgroundTexture.loadFromFile(background_path)) {
			throw std::invalid_argument("Erro ao carregar a imagem de plano de fundo! Verifique se ela está no caminho " + background_path);
		}

		backgroundSprite.setPosition({0,0});
		backgroundSprite.setScale({
		static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
		static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
	});

	}

	virtual ~Scene() = default;
	virtual void handleEvents(std::optional<sf::Event> event) = 0;
	virtual void update() = 0;
};
