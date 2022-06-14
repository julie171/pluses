#include "Rectangle.hpp"

float Rectangle::x() const {
	return rectangle.getPosition().x;
}
float Rectangle::y() const {
	return rectangle.getPosition().y;
}
float Rectangle::leftSide() const {
	return rectangle.getPosition().x - rectangle.getSize().x / 2.f;
}
float Rectangle::rightSide() const {
	return rectangle.getPosition().x + rectangle.getSize().x / 2.f;
}
float Rectangle::topSide() const {
	return rectangle.getPosition().y - rectangle.getSize().y / 2.f;
}
float Rectangle::bottomSide() const {
	return rectangle.getPosition().y + rectangle.getSize().y / 2.f;
}

void Bonus::update() {
	rectangle.move(Bonus::velocity);
	Bonus::velocity.x = 0.f;
	Bonus::velocity.y = bonusVelocity;
}

bool Bonus::isAtBottom() {
	if (bottomSide() > windowHeight)
		return true;
	return false;
}

void MovingBlock::update() {
	rectangle.move(velocity);
	if (leftSide() <= 0)
		velocity.x = movBlockVelocity;
	else if (rightSide() >= windowWidth)
		velocity.x = -movBlockVelocity;
}

void Paddle::update() {
	rectangle.move(velocity);
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && leftSide() > 0)
		velocity.x = -paddleVelocity;
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && rightSide() <
		windowWidth)
		velocity.x = paddleVelocity;
	else
		velocity.x = 0;
}