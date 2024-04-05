#include "Ball.h"

#include <iostream>

#define PI 3.14159265

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
		mBallSpeed = 500;
	}
	if (mPosition.y() < 0 || mPosition.y() + mRadius > SCREEN_HEIGHT)
	{
		mPosition += Vector2(0.0, mVelY > 0.0 ? -padding : padding);
		mVelY *= -1;
		mBallSpeed = 1000;
	}
	//std::cout << mPosition.x() << '\t' << mPosition.y() << '\t' << mVelX << '\t' << mVelY << '\n';
}

void Ball::CollideWithPaddle(const Paddle& paddle)
{
	Vector2 paddlePos{ paddle.GetPosition() };
	double paddleTop{ paddlePos.y() };
	double paddleLeft{ paddlePos.x() };
	double paddleBot{ paddleTop + paddle.GetHeight() };
	double paddleRight{ paddleLeft + paddle.GetWidth() };

	double ballTop{ mPosition.y() };
	double ballLeft{ mPosition.x() };
	double ballBot{ ballTop + mRadius };
	double ballRight{ ballLeft + mRadius };

	// cases for no contact
	if (ballBot < paddleTop) return;
	else if (ballTop > paddleBot) return;
	else if (ballRight < paddleLeft) return;
	else if (ballLeft > paddleRight) return;

	double paddleMid{ (paddleLeft + paddleRight) / 2 };
	double ballMid{ (ballLeft + ballRight) / 2 };
	mPosition += Vector2(0.0, -5.0);
	// ball contact with left of paddle
	if (ballMid < paddleMid)
	{
		mVelX = -1;
		mVelY = -tan(PI / 6);
		//std::cout << "contact LEFT!";
	}
	else // ball contact with right
	{
		mVelX = 1;
		mVelY = -tan(PI / 6);
		//std::cout << "contact RIGHT!";
	}
	std::cout << mPosition.x() << '\t' << mPosition.y() << '\t' << mVelX << '\t' << mVelY << '\n';
}

void Ball::Render()
{
	SDL_SetRenderDrawColor(gRenderer, GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE, 0xFF);
	SDL_Rect ballRect = { mPosition.x(), mPosition.y(), mRadius, mRadius };
	SDL_RenderFillRect(gRenderer, &ballRect);
}
