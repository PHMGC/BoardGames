#include "UI/ReversiScene.hpp"

//#include "UI/SceneManager.hpp"

void ReversiScene::init() {
	player1.setText(sceneManager->getCurrentPlayers()[0]);
	player2.setText(sceneManager->getCurrentPlayers()[1]);
}
