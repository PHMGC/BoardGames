#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <utility>

constexpr sf::Color YELLOW(247,230,83,255);
constexpr sf::Color ORANGE(177,49,78,255);
constexpr sf::Color BLACK(0,0,0,255);
constexpr sf::Color BLUE(54,89,185,0);
constexpr sf::Color PINK(246,115,200,200);
constexpr sf::Color RED(214,61,60,255);

class TextComponent {
	sf::Text text;
	std::vector<sf::Text> shadows;
	sf::Font font;
	int size;
	sf::Vector2f pos;
	std::vector<sf::Color> colors;
	std::vector<float> shadows_offset;

public:
	TextComponent(const std::string& textStr, const sf::Font &font, const int size,
		const sf::Vector2f& pos, const std::vector<float>& shadows_offset,
		const std::vector<sf::Color>& colors = {YELLOW, ORANGE, BLACK})
		: text(font),
		  shadows{sf::Text(font), sf::Text(font)},
		  font(font),
		  size(size),
		  pos(pos),
		  colors(colors),
		  shadows_offset(shadows_offset) {

		if (colors.size() != shadows_offset.size() + 1) {
			throw std::invalid_argument("TextComponent must have the number of colors == number of shadows offset + 1");
		}


		// Configurar o texto principal
		text.setString(textStr);
		text.setCharacterSize(size);
		text.setFillColor(colors[0]);
		text.setPosition(pos);

		for (std::size_t i = 0; i < shadows.size(); ++i) {
			shadows[i] = text;
			shadows[i].setFillColor(colors[i + 1]);
			shadows[i].setPosition(sf::Vector2f(pos.x + shadows_offset[i], pos.y + shadows_offset[i]));
		}
	}

	sf::Text& getText() {
		return text;
	}

	void rotate(const sf::Angle degrees) {
		this->text.setRotation(degrees);
		for (auto& shadow : shadows) {
			shadow.setRotation(degrees);
		}
	}

	void draw(sf::RenderTarget& window) {
		// Desenhar sombras primeiro
		for (const auto& shadow : shadows) {
			window.draw(shadow);
		}
		// Desenhar texto principal
		window.draw(text);
	}


};
