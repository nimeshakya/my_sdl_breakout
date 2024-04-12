#include "Ball.h"

#include <iostream>

void Ball::Update(double deltaTime)
{
	mPosition += Vector2(mVelX, mVelY) * mBallSpeed * deltaTime;
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
	}
	else
	{
		mPosition += Vector2(collisionType == CollisionType::COLLISION_LEFT ? padding : -padding);
		mVelX *= -1;
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

	// increase ball speed 
	if (mBallSpeed < BALL_SPEED_1) mBallSpeed = BALL_SPEED_1;

	double paddleMid{ (paddleLeft + paddleRight) / 2 };
	double ballMid{ (ballLeft + ballRight) / 2 };
	mPosition += Vector2(0.0, -5.0);

	double changeX{ 0.0 };
	if (ballMid <= paddleLeft)
	{
		changeX = -1.0;
	}
	else if (ballMid >= paddleRight)
	{
		changeX = 1.0;
	}
	else if (ballMid < paddleMid || ballMid > paddleMid)
	{
		changeX = (ballMid - paddleMid) / (paddleMid - paddleLeft);
	}
	else
	{
		changeX = 0.0;
	}

	// calculation for ball's angeld movement
	double ballAngle{ std::atan(changeX) };
	double changeY{ mVelY > 0 ? -std::cos(ballAngle) : std::cos(ballAngle)};

	mVelX = changeX;
	mVelY = changeY;


	//std::cout << mPosition.x() << '\t' << mPosition.y() << '\t' << mVelX << '\t' << mVelY << '\n';
}

void Ball::CheckBrickCollision(std::vector<Brick>& bricks, GameManager& gameManager)
{
	for (int i = 0; i < bricks.size(); ++i)
	{
		if (CollideWithBrick(bricks[i], gameManager))
		{
			bricks.erase(bricks.begin() + i);
			--i;
		}
	}
}

bool Ball::CollideWithBrick(const Brick& brick, GameManager& gameManager)
{
	Vector2 brickPos{ brick.GetPosition() };
	double brickTop{ brickPos.y() };
	double brickLeft{ brickPos.x() };
	double brickBot{ brickTop + brick.GetHeight() };
	double brickRight{ brickLeft + brick.GetWidth() };

	double ballTop{ mPosition.y() };
	double ballLeft{ mPosition.x() };
	double ballBot{ ballTop + mRadius };
	double ballRight{ ballLeft + mRadius };

	// cases for no contact
	if (ballBot < brickTop) return false;
	else if (ballTop > brickBot) return false;
	else if (ballRight < brickLeft) return false;
	else if (ballLeft > brickRight) return false;

	switch (brick.Level())
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		if (mBallSpeed > BALL_SPEED_2) break;
		mBallSpeed = BALL_SPEED_2;
		break;
	case 3:
		if (mBallSpeed > BALL_SPEED_2) break;
		mBallSpeed = BALL_SPEED_2;
		break;
	case 4:
		if (mBallSpeed > BALL_SPEED_3) break;
		mBallSpeed = BALL_SPEED_3;
		break;
	default:
		break;
	}

	// increase score
	gameManager.IncrementScore();

	// collision overlap on axes
	double collisionX{ (ballRight - brickLeft) >= (brickRight - ballLeft) ? brickRight - ballLeft : ballRight - brickLeft };
	double collisionY{ (ballBot - brickTop) >= (brickBot - ballTop) ? brickBot - ballTop : ballBot - brickTop };

	double padding{ 10.0 }; // offset so that ball don't penetrate object and does double collision detection
	mPosition += Vector2(0.0, mVelY > 0.0 ? -padding : padding);

	if (collisionX > collisionY)
	{
		// ball has collided on longer length of brick
		mVelY *= -1;
	}
	else
	{
		// ball collided on shorter length (side) of brick
		mVelX *= -1;
	}

	return true;
}

void Ball::ResetPosition()
{
	mBallSpeed = BALL_SPEED_0;
	if (mVelX > 0.0)
	{
		mPosition = Vector2(SCREEN_WIDTH - UNIT_LEN * 2, SCREEN_HEIGHT / 2 + UNIT_LEN * 2);
		mVelX = -1.0;
		mVelY = 1.0;
	}
	else
	{
		mPosition = Vector2(UNIT_LEN * 2, SCREEN_HEIGHT / 2 + UNIT_LEN * 2);
		mVelX = 1.0;
		mVelY = 1.0;
	}
}

void Ball::HandleOutOfBound(GameManager& gameManager)
{
	if (mPosition.y() + mRadius >= SCREEN_HEIGHT)
	{
		gameManager.DecrementLife();
		ResetPosition();
		gameManager.Pause();
	}
}

void Ball::Render()
{
	SDL_SetRenderDrawColor(gRenderer, GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE, 0xFF);
	SDL_Rect ballRect = { mPosition.x(), mPosition.y(), mRadius, mRadius };
	SDL_RenderFillRect(gRenderer, &ballRect);
}
