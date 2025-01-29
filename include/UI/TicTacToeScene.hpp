#pragma once

#include "UI/SceneManager.hpp"

class TicTacToeScene : public Scene {
	ImageComponent board;
	TextComponent player1;
	TextComponent player2;
	TextComponent back;

public:
	TicTacToeScene(GameManager& gameManager, sf::RenderWindow& window, SceneManager* sceneManager, const std::string& font_path)
	:	Scene(gameManager, window, sceneManager, font_path),
		board("../assets/games/ttt.png"),
		player1("",		font, 25, {300, 625}, {2, 4}),
		player2("",		font, 25, {300, 625}, {2, 4}),
		back("Voltar",	font, 25, {300, 625}, {2, 4})
	{}

	void init();


	void handleEvents(const std::optional<sf::Event> event) override {
		std::cout << "TicTacToeScene::handleEvents" << std::endl;
	}

	void draw() override {
		board.draw(window);
		player1.draw(window);
		player2.draw(window);
	}
};
