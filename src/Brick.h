#ifndef BRICK_H
#define BRICK_H

#include <SDL.h>

#include "GameWindow.h"
#include "Vector2.h"

class Brick
{
public:
	Brick(double x = 0, double y = 0, double width = 0, double height = 0, Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0x00) : mPosition{ x, y }, mWidth{ width }, mHeight{ height }, red{ r }, green{ g }, blue{ b } {}
	
	void Render();
private:
	Vector2 mPosition;
	double mWidth;
	double mHeight;
	Uint8 red;
	Uint8 green;
	Uint8 blue;
};

#endif // !BRICK_H
