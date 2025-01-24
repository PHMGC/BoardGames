#pragma once

#include <map>
#include <memory>
#include <string>
#include <stdexcept>

#include "MenuScene.hpp"
#include "LoginScene.hpp"

enum class SceneType { MENU, LOGIN, GAME_SELECTION, TICTACTOE, REVERSI, LIG4 };

inline std::string scene2String(const SceneType sceneType) {
	switch (sceneType) {
	case SceneType::MENU:
		return "Menu";
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
	std::map<SceneType, std::unique_ptr<Scene>> scenes;
	SceneType currentScene;

public:
	explicit SceneManager(sf::RenderWindow& window) {
		scenes[SceneType::MENU] = std::make_unique<MenuScene>(window, this, "../assets/joystix.otf", "../assets/menu.png");
		scenes[SceneType::LOGIN] = std::make_unique<LoginScene>(window, this, "../assets/joystix.otf", "../assets/menu.png");
		scenes[SceneType::GAME_SELECTION] = std::make_unique<MenuScene>(window, this, "../assets/joystix.otf", "../assets/menu.png");

		currentScene = SceneType::LOGIN;
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

	void update() {
		if (scenes[currentScene]) {
			scenes[currentScene]->update();
		}
	}
};
