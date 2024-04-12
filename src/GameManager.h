#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <vector>

#include <SDL.h>

#include "GameWindow.h"
#include "Brick.h"
#include "Score.h"

class GameManager
{
public:
	GameManager();

	// Returns the events
	SDL_Event* GetEvents();

	// Handle Events (general)
	void HandleEvents();

	// handle game states in here
	void Update();

	// Load the bricks Bricks (fille the vector array)
	void LoadBricks(std::vector<Brick>& brickArr);

	// clear renderer
	void RenderClear();
	// Places all the renderes
	void RenderPresent();

	// Has quit game
	bool HasQuit();
	// quit game
	void Quit();

	// score management
	void IncrementScore();
	void DecrementLife();
	void IncrementSet();
	void RenderScore();
	void ResetScore();

	void Pause();
	void UnPause();

	void SetEnd();
	void UnsetEnd();

	bool IsPaused() const { return paused; }
	bool IsSetEnd() const { return setEnd; }
	bool IsGameOver() const { return gameOver; }
private:
	bool mQuit; // flag to quit game
	SDL_Event e; // events
	Score score;
	bool paused;
	bool setEnd;
	bool gameOver;
};

#endif // !GAMEMANAGER_H