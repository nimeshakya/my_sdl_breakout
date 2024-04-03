#include <iostream>

#include <SDL.h>

#include "GameWindow.h"
#include "GameManager.h"
#include "Paddle.h"
#include "Ball.h"

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
			
			Ball ball;

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

				if (deltaTime > 0.5) return 0.5; // Cap to this value of delta time

				// Game updates here
				paddle.Update(deltaTime);

				ball.CollideWithBorder();
				ball.Update(deltaTime);

				// update tick
				lastUpdate = currentTick;

				gameManager.RenderClear();
				paddle.Render();
				ball.Render();
				gameManager.RenderPresent();
			}
		}
	}

	close();
	return 0;
}