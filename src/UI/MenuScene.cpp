#include "UI/MenuScene.hpp"

#include <iostream>
#include "UI/SceneManager.hpp"

void MenuScene::handleAction(int index) {
    	switch (index) {
    	case 1:
    		scene_manager->setCurrentScene(SceneType::LOGIN);
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