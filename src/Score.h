#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <sstream>

#include "GameWindow.h"
#include "Texture.h"

class Score
{
public:
	Score();
	~Score();

	void IncrementScore();
	void DecrementLife();
	void IncrementSet();

	void ResetScore();

	void LoadIntTextTexture(int textInt, Texture& textTexture);
	void LoadScoreTextTexture();
	// render score texts
	void Render();

	int GetLives() const { return mLives; }
private:
	int mCurrentScore;
	int mLives;
	int mCurrentSet;
	Texture mScoreTextTexture;
	Texture mLivesTextTexture;
	Texture mSetTextTexture;
};

#endif // !SCORE_H
