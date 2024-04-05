#ifndef BALL_H
#define BALL_H

#include "GameWindow.h"
#include "Vector2.h"
#include "Paddle.h"

class Ball
{
public:
	Ball(double x = 0.0, double y = 0.0) : mPosition{ x, y }, mRadius{ UNIT_LEN }, mBallSpeed{ 500 }, mVelX{ 1.0 }, mVelY{ 1.0 } {}

	void Update(double deltaTime);
	void CollideWithBorder();

	void CollideWithPaddle(const Paddle& paddle);

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