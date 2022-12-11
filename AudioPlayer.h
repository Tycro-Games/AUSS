#pragma once
#include <SDL_mixer.h>
class AudioPlayer
{
public:
	AudioPlayer();
	~AudioPlayer();
	void PlaySound();
private:
	//The music that will be played
	Mix_Music* music = nullptr;

	//sounds that will be played
	Mix_Chunk* playerShootingSound = nullptr;
};
