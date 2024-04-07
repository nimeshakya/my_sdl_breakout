#include "Ball.h"

#include <iostream>

#define PI 3.14159265

void Ball::Update(double deltaTime)
{
	mPosition += Vector2(mVelX, mVelY) * mBallSpeed * deltaTime;
	if (mPosition.y() + mRadius >= SCREEN_HEIGHT)
	{
		ResetPosition();
	}
}

void Ball::CollideWithBorder(const Border& border, CollisionType collisionType)
{
	Vector2 borderPos{ border.GetPosition() };
	double borderTop{ borderPos.y() };
	double borderLeft{ borderPos.x() };
	double borderBot{ borderTop + border.GetHeight() };
	double borderRight{ borderLeft + border.GetWidth() };

	double ballTop{ mPosition.y() };
	double ballLeft{ mPosition.x() };
	double ballBot{ ballTop + mRadius };
	double ballRight{ ballLeft + mRadius };

	// cases for no contact
	if (ballBot < borderTop) return;
	else if (ballTop > borderBot) return;
	else if (ballRight < borderLeft) return;
	else if (ballLeft > borderRight) return;

	int padding{ 5 }; // so that ball don't act weird

	if (collisionType == CollisionType::COLLISION_TOP)
	{
		mPosition += Vector2(0.0, padding);
		mVelY *= -1;
		mBallSpeed = 1000;
	}
	else
	{
		mPosition += Vector2(collisionType == CollisionType::COLLISION_LEFT ? padding : -padding);
		mVelX *= -1;
		mBallSpeed = 500;
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

void Ball::ResetPosition()
{
	mBallSpeed = 500;
	if (mVelX > 0.0)
	{
		mPosition = Vector2(SCREEN_WIDTH - UNIT_LEN * 2, UNIT_LEN * 5);
		mVelX = -1.0;
		mVelY = 1.0;
	}
	else
	{
		mPosition = Vector2(UNIT_LEN * 2, UNIT_LEN * 5);
		mVelX = 1.0;
		mVelY = 1.0;
	}
}

void Ball::Render()
{
	SDL_SetRenderDrawColor(gRenderer, GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE, 0xFF);
	SDL_Rect ballRect = { mPosition.x(), mPosition.y(), mRadius, mRadius };
	SDL_RenderFillRect(gRenderer, &ballRect);
}
