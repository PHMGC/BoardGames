#include "UI/GameSelectionScene.hpp"
#include "UI/SceneManager.hpp"

void GameSelectionScene::handleAction() {
    if (buttonIndex == 0) {
        reset();
        sceneManager->setCurrentScene(SceneType::MENU);
    }
    if(buttonIndex == 1) {
        if (gameIndex == 0) {
            reset();
            sceneManager->setCurrentScene(SceneType::LIG4);
        }
        if (gameIndex == 1) {
            reset();
            sceneManager->setCurrentScene(SceneType::TICTACTOE);
        }
        if (gameIndex == 2) {
            reset();
            sceneManager->setCurrentScene(SceneType::REVERSI);
        }
    }
}