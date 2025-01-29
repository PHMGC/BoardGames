#include "UI/Lig4Scene.hpp"

#include "UI/SceneManager.hpp"

void Lig4Scene::init() {
	player1.setText(sceneManager->getCurrentPlayers()[0]);
	player2.setText(sceneManager->getCurrentPlayers()[1]);
}
