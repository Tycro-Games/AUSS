#pragma once
#include <SDL_mixer.h>
#include "AudioID.h"


namespace Tmpl8 {
	class AudioPlayer
	{
	public:
		AudioPlayer();
		~AudioPlayer();
		void PlaySound(SoundID id);
		void PlayMusic();
		void PauseMusic();
		void SwitchMute();
		bool IsMuted()const;

	private:
		enum class channels {
			shootings,
			explosions,
			spawnings,
			misc,
			UI,
		};
		bool mute = false;
		//The music that will be played
		Mix_Music* menuMusic = nullptr;
		Mix_Music* gameMusic = nullptr;

		//sounds that will be played
		Mix_Chunk* playerShootingSound = nullptr;
	};
}