#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "GameWindow.h"
#include "GameManager.h"
#include "Paddle.h"
#include "Ball.h"
#include "Border.h"
#include "Brick.h"
#include "Score.h"

// Initialize SDL and subsystems
bool init();
// Load all media
bool loadmedia();
// Shut down SDL and subsystems
void close();

// Global variable initialization
SDL_Window* gWindow{ NULL };
SDL_Renderer* gRenderer{ NULL };
TTF_Font* gFont{ NULL };

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
	
	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "SDL_image could not be initialized! SDL_image ERROR: " << IMG_GetError() << '\n';
		return !success;
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not be initialized! SDL_ttf ERROR: " << TTF_GetError() << '\n';
		return !success;
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not be initialized! SDL_mixer ERROR: " << Mix_GetError() << "\n";
		return !success;
	}

	return success;
}

bool loadmedia()
{
	bool success{ true };

	// load global font
	gFont = TTF_OpenFont("assets/Retro Gaming.TTF", 40);
	if (gFont == NULL)
	{
		std::cout << "Failed to load font! SDL_ttf ERROR: " << TTF_GetError() << '\n';
		return !success;
	}

	return success;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;

	// Shut down subsystems
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
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

			Border borderTop(0, UNIT_LEN * 3, SCREEN_WIDTH, UNIT_LEN * 2);
			Border borderLeft(0, UNIT_LEN * 3, UNIT_LEN * 2, SCREEN_HEIGHT - UNIT_LEN * 3);
			Border borderRight(SCREEN_WIDTH - UNIT_LEN * 2, UNIT_LEN * 3, UNIT_LEN * 2, SCREEN_HEIGHT - UNIT_LEN * 3);
			
			Ball ball;

			// bricks
			std::vector<Brick> brickArr{};
			// load bricks
			gameManager.LoadBricks(brickArr);

			// scores
			Score score;

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

				if (!gameManager.IsPaused() && !gameManager.IsGameOver())
				{
					ball.CheckBrickCollision(brickArr, gameManager);
					ball.CollideWithBorder(borderTop, CollisionType::COLLISION_TOP);
					ball.CollideWithBorder(borderLeft, CollisionType::COLLISION_LEFT);
					ball.CollideWithBorder(borderRight, CollisionType::COLLISION_RIGHT);
					ball.CollideWithPaddle(paddle);
					ball.Update(deltaTime);
					ball.HandleOutOfBound(gameManager);
				}

				if (brickArr.size() <= 0)
				{
					gameManager.Pause();
					gameManager.SetEnd();
					gameManager.LoadBricks(brickArr);
					ball.ResetPosition();
				}

				if (gameManager.IsPaused() && gameManager.IsGameOver())
				{
					brickArr.clear();
					gameManager.LoadBricks(brickArr);
					gameManager.UnPause(); // so that this won't run again
					ball.ResetPosition();
				}

				gameManager.Update();
				// update tick
				lastUpdate = currentTick;

				gameManager.RenderClear();

				gameManager.RenderScore();
				borderTop.Render();
				borderLeft.Render();
				borderRight.Render();
				paddle.Render();

				if (!gameManager.IsPaused() && !gameManager.IsGameOver()) ball.Render();

				if (!gameManager.IsSetEnd() && !gameManager.IsGameOver())
				{
					for (auto brick : brickArr)
					{
						brick.Render();
					}
				}

				if (gameManager.IsPaused() || gameManager.IsGameOver())
				{
					gameManager.RenderStartGameText();
				}

				gameManager.RenderPresent();
			}
		}
	}

	close();
	return 0;
}