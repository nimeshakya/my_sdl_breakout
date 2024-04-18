#ifndef AUDIO_H
#define AUDIO_H

#include <SDL_mixer.h>

enum class SoundNames
{
	WALL_SFX,
	PADDLE_SFX,
	LAYER_0_SFX,
	LAYER_1_SFX,
	LAYER_2_SFX,
	LAYER_3_SFX,
	LAYER_4_SFX,
};

class Audio
{
public:
	Audio();
	~Audio();
	
	void PlaySound(SoundNames soundName);
private:
	Mix_Chunk* mWallSound;
	Mix_Chunk* mPaddleSound;
	Mix_Chunk* mLayer0Sound;
	Mix_Chunk* mLayer1Sound;
	Mix_Chunk* mLayer2Sound;
	Mix_Chunk* mLayer3Sound;
	Mix_Chunk* mLayer4Sound;
};

#endif // !AUDIO_H
