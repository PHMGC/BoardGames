#include <iostream>
#include "UI/SceneManager.hpp"

#include "UI/LoginScene.hpp"

void LoginScene::handleAction(const int index) {
    switch (index) {
    case 3:
    	scene_manager->setCurrentScene(SceneType::MENU);
    	break;
    default:
    	break;
    }
}