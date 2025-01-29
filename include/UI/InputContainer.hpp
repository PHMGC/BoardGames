#pragma once

#include <iostream>

#include "TextComponent.hpp"
#include "ImageContainer.hpp"

#include <SFML/Graphics.hpp>
#include <string>

struct InputContainer {
    TextComponent label;
    sf::RectangleShape box;
    sf::Text text;
    std::string input;
    static constexpr size_t MAX_INPUT_SIZE = 19;
    ImageComponent checkmark;
    ImageComponent cross;
	bool isHover = false;
    bool isTyping = false;
	bool isInputValid = true;
	bool hasEnteredInput = false;

	std::string default_placeholder;
	std::string placeholder;


    InputContainer(const std::string& labelText, const std::string& placeholderText, const sf::Font& font, const unsigned int fontSize, const sf::Vector2f pos);

    void configureBox(const sf::Vector2f& pos);

    void configureLabelAndText(const sf::Vector2f& pos);

    void configureIcons(const sf::Vector2f& pos);

	void updateInput(char typedChar);


	void setInvalidWarning(bool enable, const std::string& warning);

	void setTyping(bool typing);

    bool hasInput() const;

    void setHover(bool hover);

	void setActive(bool active);

    void draw(sf::RenderWindow& window);

	void reset();
};