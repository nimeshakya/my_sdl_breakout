#ifndef PADDLE_H
#define PADDLE_H
#include <SDL.h>

#include "GameWindow.h"
#include "Vector2.h"

class Paddle
{
public:
	Paddle(double x = 0.0, double y = 0.0) : mPosition{ x, y }, mPaddleSpeed{ 1200.0 }, mVelX { 0.0 }, mWidth{ UNIT_LEN * 6 }, mHeight{ UNIT_LEN } {}

	void Update(double deltaTime);

	// Handle paddle control inputs
	void HandleInput();

	void Render();

	Vector2 GetPosition() const { return mPosition; }
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
private:
	Vector2 mPosition;
	double mPaddleSpeed;
	double mVelX;
	int mWidth;
	int mHeight;
};
#endif // !PADDLE_H
