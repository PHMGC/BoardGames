#pragma once
#include "ParallaxComponent.hpp"


class BillboardComponent {
	ImageComponent layer;

	sf::Clock clock;
	float startTimeHorizontal = 0.0f;
	float startTimeVertical = 0.0f;
	bool wantToMoveHorizontally = false;
	bool wantToMoveVertically= false;
	float horizontalSpeed = 0.0f;
	float verticalSpeed = 0.0f;
	bool toggleVerticalDirection = false;
	bool toggleHorizontalDirection = false;
public:
	explicit BillboardComponent(const std::string& frame_path)
	: layer(frame_path) {
		layer.sprite.setPosition({layer.sprite.getPosition().x, 1080});
	}

private:
	void moveHorizontally(float speed, float duration) {
		if (!wantToMoveHorizontally) return;

		horizontalSpeed = toggleHorizontalDirection ? speed : speed * -1;

		if (clock.getElapsedTime().asSeconds() - startTimeHorizontal > duration) {
			wantToMoveHorizontally = false;
			horizontalSpeed = 0;
		}

		float x = layer.sprite.getPosition().x + horizontalSpeed;
		layer.sprite.setPosition({x, layer.sprite.getPosition().y});
	}

	void moveVertically(float speed, float duration) {
		if (!wantToMoveVertically) return;

		verticalSpeed = toggleVerticalDirection ? speed : speed * -1;
		if (clock.getElapsedTime().asSeconds() - startTimeVertical > duration) {
			verticalSpeed = 0;
			wantToMoveVertically = false;
			toggleVerticalDirection = !toggleVerticalDirection;
		}

		float y = std::clamp(layer.sprite.getPosition().y + verticalSpeed, 0.0f, 1080.0f);

		layer.sprite.setPosition({layer.sprite.getPosition().x, y});
	}

public:

	void startHorizontalAnimation(bool isLeftDirection) {
		startTimeHorizontal = clock.getElapsedTime().asSeconds();
		wantToMoveHorizontally = true;
		toggleHorizontalDirection = isLeftDirection;
	}

	void startVerticalAnimation() {
		startTimeVertical = clock.getElapsedTime().asSeconds();
		wantToMoveVertically = true;
	}

	void reset() {
		layer.sprite.setPosition({0, 1080});
	}

	void draw(sf::RenderWindow& window) {
		moveHorizontally(12, 1.73);
		moveVertically(12, 1.5);
		layer.draw(window);
	}

};
