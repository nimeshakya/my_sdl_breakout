#include "Audio.h"

Audio::Audio()
{
	mWallSound = Mix_LoadWAV("assets/wall.wav");
	mPaddleSound = Mix_LoadWAV("assets/paddle.wav");
	mLayer0Sound = Mix_LoadWAV("assets/layer0.wav");
	mLayer1Sound = Mix_LoadWAV("assets/layer1.wav");
	mLayer2Sound = Mix_LoadWAV("assets/layer2.wav");
	mLayer3Sound = Mix_LoadWAV("assets/layer3.wav");
	mLayer4Sound = Mix_LoadWAV("assets/layer4.wav");

	// volume adjustments
	mWallSound->volume = 50;
	mPaddleSound->volume = 50;
	mLayer0Sound->volume = 50;
	mLayer1Sound->volume = 50;
	mLayer2Sound->volume = 50;
	mLayer3Sound->volume = 50;
	mLayer4Sound->volume = 50;
}

Audio::~Audio()
{
	Mix_FreeChunk(mWallSound);
	Mix_FreeChunk(mPaddleSound);
	Mix_FreeChunk(mLayer0Sound);
	Mix_FreeChunk(mLayer1Sound);
	Mix_FreeChunk(mLayer2Sound);
	Mix_FreeChunk(mLayer3Sound);
	Mix_FreeChunk(mLayer4Sound);

	mWallSound = NULL;
	mPaddleSound = NULL;
	mLayer0Sound = NULL;
	mLayer1Sound = NULL;
	mLayer2Sound = NULL;
	mLayer3Sound = NULL;
	mLayer4Sound = NULL;
}

void Audio::PlaySound(SoundNames soundName)
{
	switch (soundName)
	{
	case SoundNames::WALL_SFX:
		Mix_PlayChannel(-1, mWallSound, 0);
		break;
	case SoundNames::PADDLE_SFX:
		Mix_PlayChannel(-1, mPaddleSound, 0);
		break;
	case SoundNames::LAYER_0_SFX:
		Mix_PlayChannel(-1, mLayer0Sound, 0);
		break;
	case SoundNames::LAYER_1_SFX:
		Mix_PlayChannel(-1, mLayer1Sound, 0);
		break;
	case SoundNames::LAYER_2_SFX:
		Mix_PlayChannel(-1, mLayer2Sound, 0);
		break;
	case SoundNames::LAYER_3_SFX:
		Mix_PlayChannel(-1, mLayer3Sound, 0);
		break;
	case SoundNames::LAYER_4_SFX:
		Mix_PlayChannel(-1, mLayer4Sound, 0);
		break;
	default:
		break;
	}
}