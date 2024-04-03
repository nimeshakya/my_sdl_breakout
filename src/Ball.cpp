#include "Ball.h"

#include <iostream>

void Ball::Update(double deltaTime)
{
	mPosition += Vector2(mVelX, mVelY) * mBallSpeed * deltaTime;
}

void Ball::CollideWithBorder()
{
	int padding{ 5 }; // so that ball don't act weird
	if (mPosition.x() < 0 || mPosition.x() + mRadius > SCREEN_WIDTH)
	{
		mPosition += Vector2((mVelX > 0.0 ? -padding : padding), 0.0);
		mVelX *= -1;
	}
	if (mPosition.y() < 0 || mPosition.y() + mRadius > SCREEN_HEIGHT)
	{
		mPosition += Vector2(0.0, mVelY > 0.0 ? -padding : padding);
		mVelY *= -1;
	}
	//std::cout << mPosition.x() << '\t' << mPosition.y() << '\t' << mVelX << '\t' << mVelY << '\n';
}

void Ball::Render()
{
	SDL_SetRenderDrawColor(gRenderer, GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE, 0xFF);
	SDL_Rect ballRect = { mPosition.x(), mPosition.y(), mRadius, mRadius };
	SDL_RenderFillRect(gRenderer, &ballRect);
}
