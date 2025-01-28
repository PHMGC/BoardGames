#pragma once

#include <SFML/Graphics.hpp>
#include <string>

constexpr sf::Color YELLOW(247,230,83,255);
constexpr sf::Color ORANGE(177,49,78,255);
constexpr sf::Color BLACK(0,0,0,255);
constexpr sf::Color BLUE(54,89,185,0);
constexpr sf::Color PINK(246,115,200,200);
constexpr sf::Color RED(214,61,60,255);
constexpr sf::Color GRAY(201, 201, 201, 255);

class TextComponent {
	sf::Text text;
	std::vector<sf::Text> shadows;
	sf::Font font;
	int size;
	sf::Vector2f pos;
	sf::Vector2f originalPos;
	std::vector<sf::Color> colors;
	std::vector<sf::Color> originalColors;
	std::vector<float> shadows_offset;
	bool enabled = true;
	bool hover = false;

public:
	TextComponent(const std::string& textStr, const sf::Font &font, const int size,
		const sf::Vector2f pos, const std::vector<float>& shadows_offset,
		const std::vector<sf::Color>& colors = {YELLOW, ORANGE, BLACK})
		: text(font),
		  shadows{sf::Text(font), sf::Text(font)},
		  font(font),
		  size(size),
		  pos(pos),
		  originalPos(pos),
		  colors(colors),
		  originalColors(colors),
		  shadows_offset(shadows_offset) {

		if (colors.size() != shadows_offset.size() + 1) {
			throw std::invalid_argument("TextComponent must have the number of colors == number of shadows offset + 1");
		}


		// Configurar o texto principal
		this->text.setString(textStr);
		this->text.setCharacterSize(size);
		this->text.setFillColor(colors[0]);
		this->text.setPosition(pos);

		for (std::size_t i = 0; i < shadows.size(); ++i) {
			this->shadows[i] = this->text;
			this->shadows[i].setFillColor(colors[i + 1]);
			this->shadows[i].setPosition(sf::Vector2f(pos.x + shadows_offset[i], pos.y + shadows_offset[i]));
		}
	}

	void setPos(sf::Vector2f pos) {
		this->pos = pos;
		this->text.setPosition(pos);
		for (std::size_t i = 0; i < shadows.size(); ++i) {
			this->shadows[i].setPosition(sf::Vector2f(pos.x + shadows_offset[i], pos.y + shadows_offset[i]));
		}
	}

	sf::Vector2f getPos() {
		return this->pos;
	}

	void resetPos() {
		this->pos = this->originalPos;
		this->text.setPosition(this->pos);
		for (std::size_t i = 0; i < shadows.size(); ++i) {
			this->shadows[i].setPosition(sf::Vector2f(this->pos.x + shadows_offset[i], this->pos.y + shadows_offset[i]));
		}
	}

	sf::FloatRect getHitbox() {
		return this->text.getGlobalBounds();
	}

	void setColor(sf::Color color) {
		this->text.setFillColor(color);
	}

	void resetColor() {
		this->text.setFillColor(originalColors[0]);
		this->shadows[0].setFillColor(originalColors[1]);
		this->shadows[1].setFillColor(originalColors[2]);
	}

	void setText(const std::string& textStr) {
		this->shadows[0].setString(textStr);
		this->shadows[1].setString(textStr);
		this->text.setString(textStr);
	}

	void setEnabled(bool enable) {
		if (enable) {
			this->text.setFillColor(this->colors[0]);
			this->shadows[0].setFillColor(this->colors[1]);
			this->shadows[1].setFillColor(this->colors[2]);
		}
		else {
			this->text.setFillColor(GRAY);
			this->shadows[0].setFillColor(BLACK);
			this->shadows[1].setFillColor(BLACK);
		}
		enabled = enable;
	}
	bool isEnabled() {
		return enabled;
	}

	void setHover(const bool enable) {
		if (enabled) {
			enable ? this->setColor(RED) : this->setColor(this->colors[0]);
		}
		hover = enable;
	}
	bool isHover() {
		return this->hover;
	}

	void rotate(const sf::Angle degrees) {
		this->text.setRotation(degrees);
		for (auto& shadow : this->shadows) {
			shadow.setRotation(degrees);
		}
	}

	void draw(sf::RenderTarget& window) {
		// Desenhar sombras primeiro
		for (int i = shadows.size() - 1; i >= 0; --i) {
			window.draw(shadows[i]);
		}
		// Desenhar texto principal
		window.draw(this->text);
	}


};
