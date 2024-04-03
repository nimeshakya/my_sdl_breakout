#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>

#include <SDL.h>

#include "GameWindow.h"

class GameManager
{
public:
	GameManager();

	// Returns the events
	SDL_Event* GetEvents();

	// Handle Events (general)
	void HandleEvents();

	// clear renderer
	void RenderClear();
	// Places all the renderes
	void RenderPresent();

	// Has quit game
	bool HasQuit();
	// quit game
	void Quit();

private:
	bool mQuit; // flag to quit game
	SDL_Event e; // events
};

#endif // !GAMEMANAGER_H