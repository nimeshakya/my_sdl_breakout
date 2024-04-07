#ifndef BALL_H
#define BALL_H

#include "GameWindow.h"
#include "Vector2.h"
#include "Paddle.h"
#include "Border.h"

enum class CollisionType
{
	COLLISION_TOP,
	COLLISION_LEFT,
	COLLISION_RIGHT,
};

class Ball
{
public:
	Ball(double x = UNIT_LEN * 2, double y = UNIT_LEN * 5) : mPosition{ x, y }, mRadius{ UNIT_LEN }, mBallSpeed{ 500 }, mVelX{ 1.0 }, mVelY{ 1.0 } {}

	void Update(double deltaTime);
	void CollideWithBorder(const Border& border, CollisionType collisionType);

	void CollideWithPaddle(const Paddle& paddle);

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