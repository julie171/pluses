#include "Collisions.hpp"

constexpr int numBlocksX{ 11 }, numBlocksY{ 4 };
float Bonus::size = blockHeight;

vector<Block> CreateBricks() {
	int id = 0;
	vector<Block> bricks;
	random_device num;
	int countIndestruct = 3 + num() % 2;
	int countAccelerat = 2;
	int health2 = 3;
	int health3 = 2;
	int with2Balls = 2;
	int withMovBlock = 2;
	for (int i = 1; i <= numBlocksX; ++i) {
		for (int j = 1; j <= numBlocksY; ++j)
			bricks.push_back({ i * (blockWidth + 3.f) + 22.f, (j + 1) * (blockHeight + 3.f) });
	}
	for (int i = 0; i < countIndestruct; ++i)
		bricks[num() % 42].health = -1;
	for (int i = 0; i < countAccelerat; ++i) {
		id = num() % 42;
		while (bricks[id].health == -1)
			id = num() % 42;
		bricks[id].isAccelerating = true;
	}
	for (int i = 0; i < health3; ++i) {
		id = num() % 43;
		while (bricks[id].health == -1 || bricks[id].isAccelerating == true)
			id = num() % 43;
		bricks[id].health = 2;
		bricks[id].maxHealth = 2;
	}
	for (int i = 0; i < health2; ++i) {
		id = num() % 43;
		while (bricks[id].health != 0 || bricks[id].isAccelerating == true)
			id = num() % 43;
		bricks[id].health = 1;
		bricks[id].maxHealth = 1;
	}
	for (int i = 0; i < with2Balls; ++i) {
		id = num() % 43;
		while (bricks[id].health != 0 || bricks[id].isAccelerating == true)
			id = num() % 43;
		bricks[id].balls2 = true;
	}
	for (int i = 0; i < withMovBlock; ++i) {
		id = num() % 43;
		while (bricks[id].health != 0 || bricks[id].isAccelerating == true || bricks[id].balls2 == true)
			id = num() % 43;
		bricks[id].movBlock = true;
	}
	return bricks;
}

void TestBalls(Paddle& paddle, int& defeats, Text& text, vector<Ball>& balls, vector<Block>& bricks, vector<Bonus>& bonuses, RenderWindow& window) {
	paddle.update();
	for (unsigned i = 0; i < balls.size(); ++i) {
		balls[i].update();
		TestCollision(paddle, balls[i]);
		for (unsigned j = 0; j < bricks.size(); ++j) {
			if (TestCollision(bricks[j], balls[i], defeats) == true) {
				if (bricks[j].balls2 == true) {
					bonuses.push_back({ bricks[j].x(), bricks[j].bottomSide() + Bonus::size, { 23, 155, 60, 160 } });
					bonuses.back().balls2 = true;
				}
				else {
					bonuses.push_back({ bricks[j].x(), bricks[j].bottomSide() + Bonus::size, { 255, 150, 122, 160 } });
					bonuses.back().movBlock = true;
				}
			}
		}
	}
	auto newEnd = remove_if(bricks.begin(), bricks.end(), [](const Block& block) {
		return block.isDestroyed;
		});
	bricks.erase(newEnd, bricks.end());
	for (unsigned i = 0; i < bricks.size(); ++i)
		window.draw(bricks[i].rectangle);
	for (unsigned i = 0; i < balls.size(); ++i) {
		if (balls[i].isAtBottom() == true)
			++defeats;
		if (i > 0)
			TestCollision(balls[i - 1], balls[i]);
		window.draw(balls[i].circle);
	}
}

void TestBonuses(vector<Bonus>& bonuses, Paddle& paddle, RenderWindow& window, vector<Ball>& balls, int& countMovBlocks, vector<MovingBlock>& movBlocks) {
	for (unsigned i = 0; i < bonuses.size(); ++i) {
		bonuses[i].update();
		window.draw(bonuses[i].rectangle);
		if (bonuses[i].isAtBottom() == true)
			bonuses.erase(bonuses.begin() + i);
		else if (TestCollision(bonuses[i], paddle) == true) {
			if (bonuses[i].balls2 == true) {
				balls.push_back({ windowWidth / 2, windowHeight / 2 });
				bonuses.erase(bonuses.begin() + i);
			}
			else {
				movBlocks.push_back({ windowWidth / 2, (countMovBlocks + 7) * (blockHeight + 3.f) });
				movBlocks.back().maxHealth = 2;
				movBlocks.back().health = 2;
				++countMovBlocks;
				bonuses.erase(bonuses.begin() + i);
			}
		}
	}
}

void MovingBlocks(RenderWindow& window, vector<MovingBlock>& movBlocks, vector<Ball>& balls, int& defeats, int& countMovBlocks) {
	for (unsigned i = 0; i < movBlocks.size(); ++i) {
		movBlocks[i].update();
		for (unsigned j = 0; j < balls.size(); ++j) {
			TestCollision(movBlocks[i], balls[j], defeats);
			if (movBlocks[i].isDestroyed == true)
				--countMovBlocks;
		}
		window.draw(movBlocks[i].rectangle);
	}
	movBlocks.erase(remove_if(movBlocks.begin(), movBlocks.end(), [](const MovingBlock& block) {
		return block.isDestroyed;
		}), movBlocks.end());
}

int main() {
	RenderWindow window{ VideoMode(windowWidth, windowHeight), "Arkanoid" };
	vector<Ball> balls;
	vector<Bonus> bonuses;
	balls.push_back({ windowWidth / 2, windowHeight / 2 });
	int defeats = 0;
	int countMovBlocks = 0;
	Paddle paddle{ windowWidth / 2, windowHeight - 50 };
	vector<Block> bricks;
	vector<MovingBlock> movBlocks;
	Font font;
	if (font.loadFromFile("Montserrat-Italic.ttf") == false)
		system("pause");
	Text text;
	text.setFont(font);
	text.setFillColor(Color::Black);
	text.setString("Defeats: 0");
	bricks = CreateBricks();
	window.setFramerateLimit(60);
	while (true) {
		window.clear(Color::Yellow);
		if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
			break;
		TestBalls(paddle, defeats, text, balls, bricks, bonuses, window);
		TestBonuses(bonuses, paddle, window, balls, countMovBlocks, movBlocks);
		MovingBlocks(window, movBlocks, balls, defeats, countMovBlocks);
		text.setString("Defeats: " + to_string(defeats));
		window.draw(paddle.rectangle);
		window.draw(text);
		window.display();
	}
	bricks.clear();
	movBlocks.clear();
	balls.clear();
	return 0;
}