#ifndef BALL_H
#define BALL_H

#include <vector>

#include "GameWindow.h"
#include "Vector2.h"
#include "Paddle.h"
#include "Border.h"
#include "Brick.h"

enum class CollisionType
{
	COLLISION_TOP,
	COLLISION_LEFT,
	COLLISION_RIGHT,
};

class Ball
{
public:
	const double BALL_SPEED_0{ 200.0 };
	const double BALL_SPEED_1{ 300.0 };
	const double BALL_SPEED_2{ 500.0 };
	const double BALL_SPEED_3{ 800.0 };
	const double BALL_SPEED_4{ 1000.0 }; // :)

	Ball(double x = UNIT_LEN * 2, double y = SCREEN_HEIGHT / 2 + UNIT_LEN * 2) : mPosition{ x, y }, mRadius{ UNIT_LEN }, mBallSpeed{ BALL_SPEED_0 }, mVelX{ 1.0 }, mVelY{ 1.0 } {}

	void Update(double deltaTime);
	void CollideWithBorder(const Border& border, CollisionType collisionType);

	void CollideWithPaddle(const Paddle& paddle); 

	void CheckBrickCollision(std::vector<Brick>& bricks);
	bool CollideWithBrick(const Brick& brick);

	void ResetPosition();

	// Render ball
	void Render();

private:
	Vector2 mPosition;
	double mRadius;
	double mBallSpeed;
	double mVelX;
	double mVelY;
};

#endif // !BALL_H