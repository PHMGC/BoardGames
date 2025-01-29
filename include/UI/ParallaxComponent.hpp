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
	const int FPS = 60;

protected:
    std::vector<std::unique_ptr<ImageComponent>> layers;
    std::vector<float> speeds;
	sf::Vector2f pos;

	sf::Vector2f WINDOW_SIZE = {1280, 720};

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
			this->layers.emplace_back(std::move(image));
			this->speeds.emplace_back(layerSpeeds[i]);
        }
        if (layers.empty()) {
            throw std::runtime_error("Nenhum layer encontrado na pasta: " + framesFolder);
        }
    }

	void setPosition(sf::Vector2f position) {
		for (auto& layer : this->layers) {
			layer->sprite.setPosition(position);
		}
		pos = position;
	}

	sf::Vector2f getPosition() {
		return pos;
	}

	void draw(sf::RenderWindow& window) {
    	for (int i = 0; i < layers.size(); i++) {
    		// Atualiza a posição horizontal do layer
    		float newXPos = layers[i]->sprite.getPosition().x - speeds[i];

    		float sizeX = layers[i]->texture.getSize().x;
    		// Garante que a posição esteja dentro dos limites da janela
    		if (newXPos < -sizeX) {
    			newXPos += sizeX;
    		} else if (newXPos > sizeX) {
    			newXPos -= sizeX;
    		}

    		// Define a nova posição e desenha o sprite principal
    		layers[i]->sprite.setPosition({newXPos, layers[i]->sprite.getPosition().y});
    		window.draw(layers[i]->sprite);

    		// Desenha o sprite auxiliar para preenchimento contínuo
    		sf::Sprite fillSprite(layers[i]->sprite);
    		fillSprite.setPosition({newXPos + sizeX - 2, layers[i]->sprite.getPosition().y});
    		window.draw(fillSprite);
    	}
    }


};
