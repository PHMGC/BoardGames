#include <iostream>
#include "UI/SceneManager.hpp"

#include "UI/LoginScene.hpp"

void LoginScene::handleAction(int index) {
    switch (index) {
    case 1:
    	scene_manager->setCurrentScene(SceneType::MENU);
    	break;
    default:
    	break;
    }
}