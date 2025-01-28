#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cmath>
#include "ImageContainer.hpp"

namespace fs = std::filesystem;

class ParallaxComponent {
    std::vector<std::pair<std::unique_ptr<ImageComponent>, float>> layers;

	const sf::Vector2i WINDOW_SIZE = {1280, 720};
	const int FPS = 60;

public:
    ParallaxComponent(const std::string& framesFolder, const std::vector<float>& layerSpeeds) {
        if (!fs::exists(framesFolder) || !fs::is_directory(framesFolder)) {
			throw std::invalid_argument("O caminho especificado não é uma pasta válida.");
		}
		const size_t layerCount = std::distance(fs::directory_iterator(framesFolder), fs::directory_iterator());
		if (layerCount != layerSpeeds.size()) {
			throw std::invalid_argument("layerCount != speeds.size()");
		}
		for (int i = 0; i < layerCount; ++i) {
			std::string filename = framesFolder + "/" + std::to_string(i + 1) + ".png";

			auto image = std::make_unique<ImageComponent>(filename);
			image->texture.setRepeated(true);
			layers.emplace_back(std::move(image), layerSpeeds[i]);
        }
        if (layers.empty()) {
            throw std::runtime_error("Nenhum layer encontrado na pasta: " + framesFolder);
        }
    }

	void draw(sf::RenderWindow& window) {
    	for (auto &[layer, speed] : layers) {
    		// Atualiza a posição horizontal do layer
    		float newXPos = layer->sprite.getPosition().x - speed;

    		// Garante que a posição esteja dentro dos limites da janela
    		if (newXPos < -WINDOW_SIZE.x) {
    			newXPos += WINDOW_SIZE.x;
    		} else if (newXPos > WINDOW_SIZE.x) {
    			newXPos -= WINDOW_SIZE.x;
    		}

    		// Define a nova posição e desenha o sprite principal
    		layer->sprite.setPosition({newXPos, 0});
    		window.draw(layer->sprite);

    		// Desenha o sprite auxiliar para preenchimento contínuo
    		sf::Sprite fillSprite(layer->sprite);
    		fillSprite.setPosition({newXPos + WINDOW_SIZE.x - 2, 0});
    		window.draw(fillSprite);
    	}
    }


};
