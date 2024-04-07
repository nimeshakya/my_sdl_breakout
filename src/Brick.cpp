#include "Brick.h"

void Brick::Render()
{
	SDL_SetRenderDrawColor(gRenderer, red, green, blue, 0xFF);
	SDL_Rect brickRect = { mPosition.x(), mPosition.y(), mWidth, mHeight };
	SDL_RenderDrawRect(gRenderer, &brickRect);
}