#include "Paddle.h"

void Paddle::Update(double deltaTime)
{
	mPosition += mVelX * mPaddleSpeed * deltaTime;
}

void Paddle::HandleInput()
{
	// scan key for continous key press
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_LEFT] && !(mPosition.x() < 0))
	{
		mVelX = -1.0;
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT] && !(mPosition.x() + mWidth > SCREEN_WIDTH))
	{
		mVelX = 1.0;
	}
	else
	{
		mVelX = 0.0;
	}
}

void Paddle::Render()
{
	SDL_SetRenderDrawColor(gRenderer, GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE, 0xFF);
	SDL_Rect paddleRect = { mPosition.x(), mPosition.y(), mWidth, mHeight };
	SDL_RenderFillRect(gRenderer, &paddleRect);
}