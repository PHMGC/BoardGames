#pragma once

#include "Scene.hpp"
#include "ImageContainer.hpp"


class GameSelectionScene : public Scene {
    ImageComponent lig4;
    ImageComponent ttt;
    ImageComponent reversi;
  	GameSelectionScene() : Scene(), lig4(), ttt(), reversi() {};
}