#include "GameWindow.h"
#include "Vector2.h"

class Ball
{
public:
	Ball(double x = 0.0, double y = 0.0) : mPosition{ x, y }, mRadius{ UNIT_LEN }, mBallSpeed{ 500 }, mVelX{ 1.0 }, mVelY{ 1.0 } {}

	void Update(double deltaTime);
	void CollideWithBorder();

	// Render ball
	void Render();

private:
	Vector2 mPosition;
	double mRadius;
	double mBallSpeed;
	double mVelX;
	double mVelY;
};