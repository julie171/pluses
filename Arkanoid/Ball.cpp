#include "Ball.hpp"

void Ball::update() {
	circle.move(velocity);
	if (leftSide() < 0)
		velocity.x = constForVeloc;
	else if (rightSide() > windowWidth)
		velocity.x = -constForVeloc;
	if (topSide() < 0)
		velocity.y = constForVeloc;
	else if (bottomSide() > windowHeight)
		velocity.y = -constForVeloc;
}

float Ball:: x() const {
	return circle.getPosition().x;
}
float Ball::y() const {
	return circle.getPosition().y;
}
float Ball::leftSide() const {
	return circle.getPosition().x - circle.getRadius();
}
float Ball::rightSide() const {
	return circle.getPosition().x + circle.getRadius();
}
float Ball::topSide() const {
	return circle.getPosition().y - circle.getRadius();
}
float Ball::bottomSide() const {
	return circle.getPosition().y + circle.getRadius();
}
bool Ball::isAtBottom() const {
	if (bottomSide() > windowHeight)
		return true;
	return false;
}