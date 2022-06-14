#include "Collisions.hpp"

void TestCollision(Paddle& paddle, Ball& ball) {
	if (isIntersecting(paddle, ball) == false)
		return;
	ball.velocity.y = -ball.constForVeloc;
	if (ball.x() < paddle.x())
		ball.velocity.x = -ball.constForVeloc;
	else
		ball.velocity.x = ball.constForVeloc;
}

bool TestCollision(Bonus& bonus, Paddle& paddle) {
	if (isIntersecting(bonus, paddle) == false)
		return false;
	return true;
}

bool TestCollision(Ball& ball1, Ball& ball2) {
	if (isIntersecting(ball1, ball2) == false)
		return false;
	ChangeVelocities(ball1, ball2);
	ChangeVelocities(ball2, ball1);
	return true;
}