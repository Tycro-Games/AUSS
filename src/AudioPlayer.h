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
			any = -1,
			enemy_hit,
			enemy_melee,
			spawnings,
			enemy_deaths,
			misc,
			ui,
		};
		bool mute = false;
		//The music that will be played
		Mix_Music* gameMusic = nullptr;

		//sounds that will be played
		Mix_Chunk* playerShootingSound = nullptr;
		Mix_Chunk* playerDamageSound = nullptr;
		Mix_Chunk* playerDeathSound = nullptr;
		Mix_Chunk* playerDashSound = nullptr;
		Mix_Chunk* enemyHitSound = nullptr;
		Mix_Chunk* enemyMeleeAtackSound = nullptr;
		Mix_Chunk* enemyShootSound = nullptr;
		Mix_Chunk* enemyDeathSound = nullptr;
		Mix_Chunk* projectileExplosionSound = nullptr;
		Mix_Chunk* hoverUi = nullptr;
		Mix_Chunk* clickUi = nullptr;
		Mix_Chunk* endWave = nullptr;


		//in milliseconds
		const int FADE_OUT_MUSIC = 500;
	};
}