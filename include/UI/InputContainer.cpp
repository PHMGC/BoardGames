#include "UI/InputContainer.hpp"

#include <iostream>

#include "TextComponent.hpp"
#include "ImageContainer.hpp"

#include <SFML/Graphics.hpp>
#include <string>


InputContainer::InputContainer(const std::string& labelText, const std::string& placeholderText, const sf::Font& font, const unsigned int fontSize, const sf::Vector2f pos)
    : label(labelText, font, fontSize, {0, 0}, {2, 4}),
	  box({300, 45}),
	  text(font, "Insira apelido", fontSize / 2),
      checkmark("../assets/checkmark.png"),
      cross("../assets/cross.png"),
      default_placeholder(placeholderText),
      placeholder(placeholderText) {
    configureBox(pos);
    configureLabelAndText(pos);
    configureIcons(pos);
}

void InputContainer::configureBox(const sf::Vector2f& pos) {
    box.setPosition(pos);
    box.setFillColor(sf::Color(50, 50, 50, 200));
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::Black);
}

void InputContainer::configureLabelAndText(const sf::Vector2f& pos) {
    label.setPos(pos + sf::Vector2f(10, -40));
    text.setPosition(pos + sf::Vector2f(5, box.getSize().y / 2 - 7));
}

void InputContainer::configureIcons(const sf::Vector2f& pos) {
    checkmark.sprite.setPosition(pos + sf::Vector2f(310, 2));
    checkmark.sprite.setScale({0.15f, 0.15f});

    cross.sprite.setPosition(pos + sf::Vector2f(310, 2));
    cross.sprite.setScale({0.15f, 0.15f});
}

void InputContainer::updateInput(char typedChar) {
    if (!isTyping) {
    	text.setString(input.empty() ? placeholder : input);
    	return;
    }

    setInvalidWarning(false, "");
    if (typedChar == '\b' && !input.empty()) {
    	input.pop_back();
    } else if (std::isprint(typedChar) && input.size() < MAX_INPUT_SIZE) {
    	input += typedChar;
    }
    text.setString(input.empty() ? placeholder : input);
}


void InputContainer::setInvalidWarning(bool enable, const std::string& warning) {
    isInputValid = !enable;
    placeholder = enable ? warning : default_placeholder;
    text.setString(enable ? placeholder : (input.empty() ? placeholder : input));
    if (enable) {
    	input.clear();
    }
}

void InputContainer::setTyping(bool typing) {
    isTyping = typing;
    text.setString(input.empty() ? placeholder : input);
}

bool InputContainer::hasInput() const {
    return !input.empty();
}

void InputContainer::setHover(bool hover) {
    isHover = hover;
    box.setOutlineColor(hover ? RED : BLACK);
}

void InputContainer::setActive(bool active) {
    setHover(active);
    isTyping = active;
}

void InputContainer::draw(sf::RenderWindow& window) {
    window.draw(box);
    label.draw(window);

    window.draw(text);
    if (hasEnteredInput) {
    	if (isInputValid) {
    		window.draw(checkmark.sprite);
    	}
    	else{
    		window.draw(cross.sprite);
    	}
    }
}

void InputContainer::reset() {
    input.clear();
    placeholder = default_placeholder;
    setInvalidWarning(false, "");
    hasEnteredInput = false;
    text.setString(placeholder);
}