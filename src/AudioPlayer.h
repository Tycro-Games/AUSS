#pragma once
#include <SDL_mixer.h>
#include "AudioID.h"


namespace Tmpl8 {
	class AudioPlayer  // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		AudioPlayer();
		~AudioPlayer();
		void PlaySound(SoundID id) const;
		void PlayMusic() const;
		void PauseMusic() const;
		void StopMusic() const;
		void SwitchMute();
		bool IsMuted()const;

	private:
		enum class channels {
			shootings,
			explosions,
			spawnings,
			misc,
			ui,
		};
		bool mute = false;
		//The music that will be played
		Mix_Music* menuMusic = nullptr;
		Mix_Music* gameMusic = nullptr;

		//sounds that will be played
		Mix_Chunk* playerShootingSound = nullptr;
		//in milliseconds
		const int FADE_OUT_MUSIC = 500;
	};
}