#include "UI/TicTacToeScene.hpp"

#include "UI/SceneManager.hpp"

void TicTacToeScene::init() {
	player1.setText(sceneManager->getCurrentPlayers()[0]);
	player2.setText(sceneManager->getCurrentPlayers()[1]);
}
