#include <iostream>
#include <vector>

#include <SDL.h>

#include "GameWindow.h"
#include "GameManager.h"
#include "Paddle.h"
#include "Ball.h"
#include "Border.h"
#include "Brick.h"

// Initialize SDL and subsystems
bool init();
// Load all media
bool loadmedia();
// Shut down SDL and subsystems
void close();

// Global variable initialization
SDL_Window* gWindow{ NULL };
SDL_Renderer* gRenderer{ NULL };

bool init()
{
	bool success{ true };

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL ERROR: " << SDL_GetError() << '\n';
		return !success;
	}

	// Define a window
	gWindow = SDL_CreateWindow("My SDL Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		std::cout << "Window could not be created! SDL ERROR: " << SDL_GetError() << '\n';
		return !success;
	}

	// Define a renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL)
	{
		std::cout << "Renderer could not be created! SDL ERROR: " << SDL_GetError() << '\n';
		return !success;
	}

	return success;
}

bool loadmedia()
{
	bool success{ true };

	// load medias here

	return success;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;

	// Shut down subsystems
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (!init())
	{
		std::cout << "Failed to initialize SDL!\n";
	}
	else
	{
		if (!loadmedia())
		{
			std::cout << "Failed to load media!\n";
		}
		else
		{
			GameManager gameManager;
			
			// Game objects
			Paddle paddle((SCREEN_WIDTH - UNIT_LEN * 6) / 2, SCREEN_HEIGHT - 3*UNIT_LEN);

			Border borderTop(0, UNIT_LEN * 5, SCREEN_WIDTH, UNIT_LEN * 2);
			Border borderLeft(0, UNIT_LEN * 5, UNIT_LEN * 2, SCREEN_HEIGHT - UNIT_LEN * 5);
			Border borderRight(SCREEN_WIDTH - UNIT_LEN * 2, UNIT_LEN * 5, UNIT_LEN * 2, SCREEN_HEIGHT - UNIT_LEN * 5);
			
			Ball ball;

			// bricks
			std::vector<Brick> brickArr{};
			// load bricks
			int brickLayWith{ SCREEN_WIDTH - UNIT_LEN * 4 };
			for (int i = 0; i < brickLayWith; ++i)
			{
				if (i % (BRICK_LEN) == 0)
				{
					Brick newBrick((double)i + UNIT_LEN * 2, SCREEN_HEIGHT / 2, BRICK_LEN, UNIT_LEN, GameObjColor::BRICK_0_RED, GameObjColor::BRICK_0_GREEN, GameObjColor::BRICK_0_BLUE, 0);
					brickArr.push_back(newBrick);
				}
			}
			for (int i = 0; i < brickLayWith; ++i)
			{
				if (i % (BRICK_LEN) == 0)
				{
					Brick newBrick((double)i + UNIT_LEN * 2, SCREEN_HEIGHT / 2 - UNIT_LEN, BRICK_LEN, UNIT_LEN, GameObjColor::BRICK_1_RED, GameObjColor::BRICK_1_GREEN, GameObjColor::BRICK_1_BLUE, 1);
					brickArr.push_back(newBrick);
				}
			}
			for (int i = 0; i < brickLayWith; ++i)
			{
				if (i % (BRICK_LEN) == 0)
				{
					Brick newBrick((double)i + UNIT_LEN * 2, SCREEN_HEIGHT / 2 - UNIT_LEN * 2, BRICK_LEN, UNIT_LEN, GameObjColor::BRICK_2_RED, GameObjColor::BRICK_2_GREEN, GameObjColor::BRICK_2_BLUE, 2);
					brickArr.push_back(newBrick);
				}
			}
			for (int i = 0; i < brickLayWith; ++i)
			{
				if (i % (BRICK_LEN) == 0)
				{
					Brick newBrick((double)i + UNIT_LEN * 2, SCREEN_HEIGHT / 2 - UNIT_LEN * 3, BRICK_LEN, UNIT_LEN, GameObjColor::BRICK_3_RED, GameObjColor::BRICK_3_GREEN, GameObjColor::BRICK_3_BLUE, 3);
					brickArr.push_back(newBrick);
				}
			}
			for (int i = 0; i < brickLayWith; ++i)
			{
				if (i % (BRICK_LEN) == 0)
				{
					Brick newBrick((double)i + UNIT_LEN * 2, SCREEN_HEIGHT / 2 - UNIT_LEN * 4, BRICK_LEN, UNIT_LEN, GameObjColor::BRICK_4_RED, GameObjColor::BRICK_4_GREEN, GameObjColor::BRICK_4_BLUE, 4);
					brickArr.push_back(newBrick);
				}
			}

			// Time calculations
			Uint32 lastUpdate{ SDL_GetTicks() };
			double deltaTime{ 0.0 };

			while (!gameManager.HasQuit())
			{
				while (SDL_PollEvent(gameManager.GetEvents()) != 0)
				{
					gameManager.HandleEvents();
				}
				// handle paddle control input (as it is continuous)
				paddle.HandleInput();

				Uint32 currentTick{ SDL_GetTicks() };
				deltaTime = (currentTick - lastUpdate) / 1000.0;

				if (deltaTime > 0.5) deltaTime = 0.5; // Cap to this value of delta time

				// Game updates here
				paddle.Update(deltaTime);

				ball.CheckBrickCollision(brickArr);
				ball.CollideWithBorder(borderTop, CollisionType::COLLISION_TOP);
				ball.CollideWithBorder(borderLeft, CollisionType::COLLISION_LEFT);
				ball.CollideWithBorder(borderRight, CollisionType::COLLISION_RIGHT);
				ball.CollideWithPaddle(paddle);
				ball.Update(deltaTime);

				// update tick
				lastUpdate = currentTick;

				gameManager.RenderClear();
				borderTop.Render();
				borderLeft.Render();
				borderRight.Render();
				paddle.Render();
				ball.Render();
				for (auto brick : brickArr)
				{
					brick.Render();
				}
				gameManager.RenderPresent();
			}
		}
	}

	close();
	return 0;
}