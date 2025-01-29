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
#include "GameSelectionScene.hpp"
#include "TicTacToeScene.hpp"
#include "Lig4Scene.hpp"
#include "ReversiScene.hpp"

enum class SceneType { MENU, SIGNUP, LOGIN, GAME_SELECTION, TICTACTOE, LIG4, REVERSI };

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

	std::string player1;
	std::string player2;

	ParallaxComponent background;

public:
	explicit SceneManager(GameManager& gameManager, sf::RenderWindow& window)
		: gameManager(gameManager), window(window),
		background("../assets/menu", {0.5, 0.5, 1.0, 1.25, 1.5, 2.0, 2.5, 0})

	{
		scenes[SceneType::MENU] = std::make_unique<MenuScene>(gameManager, window, this, "../assets/PressStart2P.ttf");
		scenes[SceneType::SIGNUP] = std::make_unique<SignUpScene>(gameManager, window, this, "../assets/PressStart2P.ttf");
		scenes[SceneType::LOGIN] = std::make_unique<SignInScene>(gameManager, window, this, "../assets/PressStart2P.ttf");
		scenes[SceneType::GAME_SELECTION] = std::make_unique<GameSelectionScene>(gameManager, window, this, "../assets/PressStart2P.ttf");
		scenes[SceneType::TICTACTOE] = std::make_unique<TicTacToeScene>(gameManager, window, this, "../assets/PressStart2P.ttf");
		scenes[SceneType::LIG4] = std::make_unique<Lig4Scene>(gameManager, window, this, "../assets/PressStart2P.ttf");
		scenes[SceneType::REVERSI] = std::make_unique<ReversiScene>(gameManager, window, this, "../assets/PressStart2P.ttf");

		currentScene = SceneType::GAME_SELECTION;
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

	void setCurrentPlayers(const std::string& player1, const std::string& player2) {
		this->player1 = player1;
		this->player2 = player2;
	}

	std::vector<std::string> getCurrentPlayers() {
		return {player1, player2};
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
