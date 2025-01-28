#pragma once

#include <SFML/Graphics.hpp>

struct ImageComponent {
	sf::Texture texture;
	sf::Sprite sprite;

	explicit ImageComponent(const std::string& texture_path)
	: texture(texture_path), sprite(texture) {
		if (!texture.loadFromFile(texture_path)) {
			throw std::runtime_error("Failed to load texture: " + texture_path);
		}
		texture.setRepeated(true);
		sprite.setTexture(texture);
	}

	void setTexture(const sf::Texture& texture) {
		this->texture = texture;
		sprite.setTexture(texture);
	}

	void draw(sf::RenderWindow& window) const {
		window.draw(sprite);
	}
};