#ifndef BORDER_H
#define BORDER_H

#include "GameWindow.h"
#include "Vector2.h"

class Border
{
public:
	Border(double x = 0, double y = 0, double w = 0, double h = 0) : mPosition{ x, y }, mWidth{ w }, mHeight{ h } {}

	void Render();

	Vector2 GetPosition() const { return mPosition; }
	double GetWidth() const { return mWidth; }
	double GetHeight() const { return mHeight; }

private:
	Vector2 mPosition;
	double mWidth;
	double mHeight;
};

#endif // !BORDER_H
