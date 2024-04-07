#include "Border.h"

void Border::Render()
{
	SDL_SetRenderDrawColor(gRenderer, GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE, 0xFF);
	SDL_Rect borderRect = { mPosition.x(), mPosition.y(), mWidth, mHeight };
	SDL_RenderFillRect(gRenderer, &borderRect);
}