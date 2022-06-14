#pragma once

#include "Ball.hpp"

void TestCollision(Paddle& paddle, Ball& ball);

bool TestCollision(Bonus& bonus, Paddle& paddle);

bool TestCollision(Ball& ball1, Ball& ball2);

template<class T1, class T2>
bool isIntersecting(T1& A, T2& B) {
	return A.rightSide() >= B.leftSide() && A.leftSide() <= B.rightSide() && A.bottomSide() >= B.topSide() && A.topSide() <= B.bottomSide();
}

template<class T1>
void ChangeVelocities(T1& shape, Ball& ball) {
	float rightIntersect = shape.rightSide() - ball.leftSide();
	float leftIntersect = shape.leftSide() - ball.rightSide();
	float topIntersect = shape.topSide() - ball.bottomSide();
	float bottomIntersect = shape.bottomSide() - ball.topSide();
	float smallestX = rightIntersect;
	float smallestY = bottomIntersect;
	if (abs(rightIntersect) >= abs(leftIntersect))
		smallestX = leftIntersect;
	if (abs(bottomIntersect) >= abs(topIntersect))
		smallestY = topIntersect;
	if (abs(smallestX) >= abs(smallestY))
		ball.velocity.y = (abs(bottomIntersect) >= abs(topIntersect) ? -ball.constForVeloc : ball.constForVeloc);
	else
		ball.velocity.x = (abs(rightIntersect) >= abs(leftIntersect) ? -ball.constForVeloc : ball.constForVeloc);
}

template<class T1>
bool TestCollision(T1& brick, Ball& ball, int& defeats) {
	if (isIntersecting(brick, ball) == false)
		return false;
	if (brick.isAccelerating == true) {
		ball.constForVeloc *= 1.25f;
		ball.velocity.x *= 1.25f;
		ball.velocity.y *= 1.25f;
	}
	if (brick.health == 0)
		brick.isDestroyed = true;
	ChangeVelocities(brick, ball);
	if (brick.maxHealth == 1 || brick.maxHealth == 2) {
		--defeats;
		--brick.health;
		brick.rectangle.setFillColor({ 0, 0, 255, 140 });
	}
	else if (brick.balls2 == true || brick.movBlock == true)
		return true;
	return false;
}