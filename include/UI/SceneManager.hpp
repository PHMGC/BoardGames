#pragma once

#include <GameManager.hpp>
#include <map>
#include <memory>
#include <string>

#include "Scene.hpp"
#include "ParallaxComponent.hpp"
#include "TextComponent.hpp"

class MenuScene;
class SignUpScene;
class SignInScene;
class GameSelectionScene;
class TicTacToeScene;
class Lig4Scene;
class ReversiScene;

enum class SceneType { MENU, SIGNUP, LOGIN, GAME_SELECTION, TICTACTOE, LIG4, REVERSI };

std::string scene2String(SceneType sceneType);

class SceneManager {
	GameManager& gameManager;
	std::map<SceneType, std::unique_ptr<Scene>> scenes;
	SceneType currentScene;
	sf::RenderWindow& window;
	std::string player1;
	std::string player2;
	ParallaxComponent background;

public:
	explicit SceneManager(GameManager& gameManager, sf::RenderWindow& window);

	void setCurrentScene(const SceneType& scene_type);
	[[nodiscard]] Scene& getCurrentScene();
	void setCurrentPlayers(const std::string& player1, const std::string& player2);
	std::vector<std::string> getCurrentPlayers();
	void handleEvents(const std::optional<sf::Event>& event);
	void draw();
};
