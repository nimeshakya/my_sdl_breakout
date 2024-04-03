#include <SDL.h>

#include "GameWindow.h"
#include "Vector2.h"

class Paddle
{
public:
	Paddle(double x = 0.0, double y = 0.0) : mPosition{ x, y }, mPaddleSpeed{ 1000.0 }, mVelX { 0.0 }, mWidth{ UNIT_LEN * 6 }, mHeight{ UNIT_LEN } {}

	void Update(double deltaTime);

	// Handle paddle control inputs
	void HandleInput();

	void Render();

private:
	Vector2 mPosition;
	double mPaddleSpeed;
	double mVelX;
	int mWidth;
	int mHeight;
};