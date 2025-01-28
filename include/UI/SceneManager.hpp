#pragma once

#include <GameManager.hpp>
#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <utility>

#include "MenuScene.hpp"
#include "SignUpScene.hpp"
#include "SignInScene.hpp"

enum class SceneType { MENU, SIGNUP, LOGIN, GAME_SELECTION, TICTACTOE, REVERSI, LIG4 };

inline std::string scene2String(const SceneType sceneType) {
	switch (sceneType) {
	case SceneType::MENU:
		return "Menu";
	case SceneType::SIGNUP:
		return "SignUp";
	case SceneType::LOGIN:
		return "Login";
	case SceneType::GAME_SELECTION:
		return "Game Selection";
	case SceneType::TICTACTOE:
		return "TicTacToe";
	case SceneType::REVERSI:
		return "Reversi";
	case SceneType::LIG4:
		return "Lig4";
	default:
		throw std::invalid_argument("Invalid SceneType");
	}
}

class SceneManager {
	GameManager& gameManager;

	std::map<SceneType, std::unique_ptr<Scene>> scenes;
	SceneType currentScene;
	sf::RenderWindow& window;

	ParallaxComponent background;

public:
	explicit SceneManager(GameManager& gameManager, sf::RenderWindow& window)
		: gameManager(gameManager), window(window),
		background("../assets/menu", {0.3, 0.6, 0.9, 1.2, 1.2, 1.5, 1.8, 0})
	{
		scenes[SceneType::MENU] = std::make_unique<MenuScene>(gameManager, window, this, "../assets/PressStart2P.ttf");
		scenes[SceneType::SIGNUP] = std::make_unique<SignUpScene>(gameManager, window, this, "../assets/PressStart2P.ttf");
		scenes[SceneType::LOGIN] = std::make_unique<SignInScene>(gameManager, window, this, "../assets/PressStart2P.ttf");
		scenes[SceneType::GAME_SELECTION] = std::make_unique<MenuScene>(gameManager, window, this, "../assets/PressStart2P.ttf");

		currentScene = SceneType::MENU;
	}

	void setCurrentScene(const SceneType& scene_type) {
		auto it = scenes.find(scene_type);
		if (it != scenes.end()) {
			currentScene = it->first;
		} else {
			throw std::runtime_error("Cena não encontrada: " + scene2String(scene_type));
		}
	}

	[[nodiscard]] Scene& getCurrentScene() {
		return *scenes[currentScene];
	}

	void handleEvents(const std::optional<sf::Event>& event) {
		if (scenes[currentScene]) {
			scenes[currentScene]->handleEvents(event);
		}
	}

	void draw() {
		window.clear();
		background.draw(window);
		if (scenes[currentScene]) {
			scenes[currentScene]->draw();
		}
		window.display();
	}
};
