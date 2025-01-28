#include "UI/MenuScene.hpp"

#include <iostream>
#include "UI/SceneManager.hpp"

void MenuScene::handleAction(int index) {
    	switch (index) {
    	case 0:
    		sceneManager->setCurrentScene(SceneType::LOGIN);
    		break;
    	case 1:
    		sceneManager->setCurrentScene(SceneType::SIGNUP);
    		break;
    	case 2:
    		std::cout << "Leaderboard acionado!" << std::endl;
    		break;
    	case 3:
    		window.close();
    		break;
    	default:
    		break;
    	}
    }