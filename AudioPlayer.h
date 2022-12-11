#pragma once
#include <SDL_mixer.h>
#include "AudioID.h"


namespace Tmpl8 {
	class AudioPlayer
	{
	public:
		AudioPlayer();
		~AudioPlayer();
		void PlaySound();
		void PlayMusic();
		void PauseMusic();
	private:
		//The music that will be played
		Mix_Music* menuMusic = nullptr;
		Mix_Music* gameMusic = nullptr;

		//sounds that will be played
		Mix_Chunk* playerShootingSound = nullptr;
	};
}