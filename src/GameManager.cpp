#include "GameManager.h"

GameManager::GameManager() : e{ NULL } // making event NULL
{
	mQuit = false;
	paused = true;
	setEnd = false;
	gameOver = false;
	Score score;
}

SDL_Event* GameManager::GetEvents()
{
	return &e;
}

void GameManager::Update()
{
	if (score.GetLives() <= 0)
	{
		gameOver = true;
	}
}

void GameManager::LoadBricks(std::vector<Brick>& brickArr)
{
	int brickLayWith{ SCREEN_WIDTH - UNIT_LEN * 4 };
	for (int i = 0; i < brickLayWith; ++i)
	{
		if (i % (BRICK_LEN) == 0)
		{
			Brick newBrick((double)i + UNIT_LEN * 2, SCREEN_HEIGHT / 2, BRICK_LEN, UNIT_LEN, GameObjColor::BRICK_0_RED, GameObjColor::BRICK_0_GREEN, GameObjColor::BRICK_0_BLUE, 0);
			brickArr.push_back(newBrick);
		}
	}
	/*for (int i = 0; i < brickLayWith; ++i)
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
	}*/
}

void GameManager::HandleEvents()
{
	if (e.type == SDL_QUIT)
	{
		mQuit = true;
	}

	if (e.type == SDL_KEYDOWN)
	{
		SDL_Keycode keysym{ e.key.keysym.sym };
		if (keysym == SDLK_p && setEnd)
		{
			IncrementSet();
			UnsetEnd();
			UnPause();
		}
		else if (keysym == SDLK_p && gameOver)
		{
			std::cout << "This one!\n";
			gameOver = false;
			paused = false;
			setEnd = false;
			ResetScore();
		}
		else if (keysym == SDLK_p)
		{
			paused = false;
		}
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

void GameManager::IncrementScore()
{
	score.IncrementScore();
}

void GameManager::DecrementLife()
{
	score.DecrementLife();
}

void GameManager::IncrementSet()
{
	score.IncrementSet();
}

void GameManager::RenderScore()
{
	score.Render();
}

void GameManager::ResetScore()
{
	score.ResetScore();
}

void GameManager::Pause()
{
	paused = true;
}

void GameManager::UnPause()
{
	paused = false;
}

void GameManager::SetEnd()
{
	setEnd = true;
}

void GameManager::UnsetEnd()
{
	setEnd = false;
}