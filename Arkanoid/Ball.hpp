#pragma once

#include "Rectangle.hpp"

constexpr float ballRadius{ 11.f }, ballVelocity{ 5.f };

class Ball {
public:
	Vector2f velocity{ -ballVelocity, -ballVelocity };
	CircleShape circle;
	float constForVeloc = ballVelocity;
	Ball(float x, float y) {
		circle.setOrigin(ballRadius, ballRadius);
		circle.setFillColor(Color::Red);
		circle.setPosition(x, y);
		circle.setRadius(ballRadius);
	}
	void update();
	float x() const;
	float y() const;
	float leftSide() const;
	float rightSide() const;
	float topSide() const;
	float bottomSide() const;
	bool isAtBottom() const;
};