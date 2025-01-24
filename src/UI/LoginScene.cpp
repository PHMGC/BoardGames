#include <iostream>
#include "UI/SceneManager.hpp"

#include "UI/LoginScene.hpp"

void LoginScene::handleAction() {
	if (currentIndex == 0) {
		player1.setTyping(true);
		player2.setTyping(false);
	}
	if (currentIndex == 1) {
		player1.setTyping(false);
		player2.setTyping(true);
	}

    if (currentIndex == 2) {
    	if (next.isEnabled()) {
    		//scene_manager->setCurrentScene(SceneType::GAME_SELECTION);
    		std::cout << "Game Selection" << std::endl;
    	}
    }
	if (currentIndex == maxIndex) {
		scene_manager->setCurrentScene(SceneType::MENU);
    }
}