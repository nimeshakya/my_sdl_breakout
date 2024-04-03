#include "GameManager.h"

GameManager::GameManager() : e{ NULL } // making event NULL
{
	mQuit = false;
}

SDL_Event* GameManager::GetEvents()
{
	return &e;
}

void GameManager::HandleEvents()
{
	if (e.type == SDL_QUIT)
	{
		mQuit = true;
	}
}

void GameManager::RenderClear()
{
	SDL_SetRenderDrawColor(gRenderer, GameObjColor::BG_RED, GameObjColor::BG_GREEN, GameObjColor::BG_BLUE, 0xFF);
	SDL_RenderClear(gRenderer);
}

void GameManager::RenderPresent()
{
	SDL_RenderPresent(gRenderer);
}

bool GameManager::HasQuit()
{
	return mQuit;
}

void GameManager::Quit()
{
	mQuit = true;
}