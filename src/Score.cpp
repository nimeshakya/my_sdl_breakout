#include "Score.h"

Score::Score() : mCurrentScore{ 0 }, mLives{ 5 }, mCurrentSet{ 1 }
{
	SDL_Color textColor = { GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE };
	if (!mScoreTextTexture.loadFromRenderedText("000", textColor))
	{
		std::cout << "Failed to load score text texture!\n";
	}
	if (!mLivesTextTexture.loadFromRenderedText(std::to_string(mLives), textColor))
	{
		std::cout << "Failed to load lives text texture!\n";
	}
	if (!mSetTextTexture.loadFromRenderedText(std::to_string(mCurrentSet), textColor))
	{
		std::cout << "Failed to load set text texture!\n";
	}
}

Score::~Score()
{
	mScoreTextTexture.free();
	mLivesTextTexture.free();
	mSetTextTexture.free();
}

void Score::IncrementScore()
{
	mCurrentScore += 1;
	LoadScoreTextTexture();
}

void Score::DecrementLife()
{
	mLives -= 1;
	LoadIntTextTexture(mLives, mLivesTextTexture);
}

void Score::IncrementSet()
{
	mCurrentSet += 1;
	LoadIntTextTexture(mCurrentSet, mSetTextTexture);
}

void Score::ResetScore()
{
	mCurrentScore = 0;
	mLives = 5;
	mCurrentSet = 1;
	LoadScoreTextTexture();
	LoadIntTextTexture(mLives, mLivesTextTexture);
	LoadIntTextTexture(mCurrentSet, mSetTextTexture);
}

void Score::LoadIntTextTexture(int textInt, Texture& textTexture)
{
	textTexture.free();
	std::stringstream textStream;
	textStream << textInt;
	std::string text;
	textStream >> text;
	SDL_Color textColor = { GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE };
	textTexture.loadFromRenderedText(text, textColor);
}

void Score::LoadScoreTextTexture()
{
	// update texture
	mScoreTextTexture.free();
	std::stringstream scoreStream;
	if (mCurrentScore < 10)
	{
		scoreStream << "00" << mCurrentScore;
	}
	else if (mCurrentScore < 100)
	{
		scoreStream << "0" << mCurrentScore;
	}
	else
	{
		scoreStream << mCurrentScore;
	}
	std::string scoreText;
	scoreStream >> scoreText;
	SDL_Color textColor = { GameObjColor::OB_RED, GameObjColor::OB_GREEN, GameObjColor::OB_BLUE };
	mScoreTextTexture.loadFromRenderedText(scoreText, textColor);
}

void Score::Render()
{
	mScoreTextTexture.Render(UNIT_LEN * 4, 0);
	mLivesTextTexture.Render((SCREEN_WIDTH - mLivesTextTexture.getWidth()) / 2, 0);
	mSetTextTexture.Render(SCREEN_WIDTH - mSetTextTexture.getWidth() - UNIT_LEN * 4, 0);
}