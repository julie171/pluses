#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include <vector>

using namespace std;
using namespace sf;

constexpr int windowWidth{ 800 }, windowHeight{ 600 };
constexpr float paddleWidth{ 80.f }, paddleHeight{ 20.f }, paddleVelocity{ 7.f };
constexpr float blockWidth{ 60.f }, blockHeight{ 20.f };
constexpr float bonusVelocity{ 6.f };
constexpr float movBlockVelocity{ 4.f };

class Rectangle {
public:
	RectangleShape rectangle;
	Vector2f velocity;
	Rectangle(float mX, float mY, float width, float height, const Color color) {
		rectangle.setOrigin(width / 2.f, height / 2.f);
		rectangle.setFillColor(color);
		rectangle.setPosition(mX, mY);
		rectangle.setSize({ width, height });
	}
	float x() const;
	float y() const;
	float leftSide() const;
	float rightSide() const;
	float topSide() const;
	float bottomSide() const;
};

class Block : public Rectangle {
public:
	Block(float x, float y) : Rectangle(x, y, blockWidth, blockHeight, Color::Blue) {}
	bool isDestroyed = false;
	bool isAccelerating = false;
	int health = 0;
	bool balls2 = false;
	int maxHealth = 0;
	bool movBlock = false;
};

class Bonus : public Rectangle {
public:
	static float size;
	Vector2f velocity;
	Bonus(float x, float y, const Color color) : Rectangle(x, y, blockHeight, blockHeight, color) {}
	void update();
	bool isAtBottom();
	bool balls2 = false;
	bool movBlock = false;
};

class MovingBlock : public Block {
public:
	Vector2f velocity{ movBlockVelocity, 0.f };
	MovingBlock(float x, float y) : Block(x, y) {}
	void update();
};

class Paddle : public Rectangle {
public:
	Paddle(float x, float y) : Rectangle(x, y, paddleWidth, paddleHeight, Color::Black) {};
	void update();
};