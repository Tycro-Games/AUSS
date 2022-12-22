#include "AudioPlayer.h"

namespace Tmpl8
{
	AudioPlayer::AudioPlayer()
	{
		gameMusic = Mix_LoadMUS("assets/Sounds&Music/gameMusic.wav");
		//sounds
		playerShootingSound = Mix_LoadWAV("assets/Sounds&Music/playerShoot.wav");
		playerDamageSound = Mix_LoadWAV("assets/Sounds&Music/playerDamage.wav");
		playerDeathSound = Mix_LoadWAV("assets/Sounds&Music/playerDeath.wav");
		playerDashSound = Mix_LoadWAV("assets/Sounds&Music/playerDash.wav");
		enemyHitSound = Mix_LoadWAV("assets/Sounds&Music/enemyHit.wav");
		enemyMeleeAttackSound = Mix_LoadWAV("assets/Sounds&Music/enemyMelee.wav");
		enemyShootSound = Mix_LoadWAV("assets/Sounds&Music/enemyShoot.wav");
		enemyDeathSound = Mix_LoadWAV("assets/Sounds&Music/enemyDeath.wav");
		projectileExplosionSound = Mix_LoadWAV("assets/Sounds&Music/projectileExplosion.wav");
		hoverUi = Mix_LoadWAV("assets/Sounds&Music/hoverUi.wav");
		clickUi = Mix_LoadWAV("assets/Sounds&Music/clickUi.wav");
		endWave = Mix_LoadWAV("assets/Sounds&Music/endWave.wav");
	}

	AudioPlayer::~AudioPlayer()
	{
		//free memory
		Mix_FreeMusic(gameMusic);

		Mix_FreeChunk(playerShootingSound);
		Mix_FreeChunk(playerDamageSound);
		Mix_FreeChunk(playerDeathSound);
		Mix_FreeChunk(playerDashSound);
		Mix_FreeChunk(enemyHitSound);
		Mix_FreeChunk(enemyMeleeAttackSound);
		Mix_FreeChunk(enemyShootSound);
		Mix_FreeChunk(enemyDeathSound);
		Mix_FreeChunk(projectileExplosionSound);
		Mix_FreeChunk(hoverUi);
		Mix_FreeChunk(clickUi);
		Mix_FreeChunk(endWave);
	}

	void AudioPlayer::PlaySound(const SoundID id) const
	{
		if (mute)
			return;
		//-1 is used for a free channel
		switch (id)
		{
		case SoundID::playerShooting:
			Mix_PlayChannel(static_cast<int>(channels::player), playerShootingSound, 0);
			break;
		case SoundID::playerDamage: // NOLINT(bugprone-branch-clone)
			Mix_PlayChannel(static_cast<int>(channels::singular), playerDamageSound, 0);

			break;
		case SoundID::playerDeath:
			Mix_PlayChannel(static_cast<int>(channels::singular), playerDeathSound, 0);

			break;
		case SoundID::playerDash:
			Mix_PlayChannel(static_cast<int>(channels::player), playerDashSound, 0);

			break;
		case SoundID::enemyHit:
			//if it is not already playing
			if (Mix_Playing(static_cast<int>(channels::enemy_hit)) == 0)
				Mix_PlayChannel(static_cast<int>(channels::enemy_hit), enemyHitSound, 0);

			break;
		case SoundID::enemyMeleeAttack:
			if (Mix_Playing(static_cast<int>(channels::enemy_melee)) == 0)
				Mix_PlayChannel(static_cast<int>(channels::enemy_melee), enemyMeleeAttackSound, 0);
			break;
		case SoundID::enemyShoot:
			if (Mix_Playing(static_cast<int>(channels::enemyShoot)) == 0)
				Mix_PlayChannel(static_cast<int>(channels::enemyShoot), enemyShootSound, 0);
			break;
		case SoundID::enemyDeath:
			if (Mix_Playing(static_cast<int>(channels::enemy_deaths)) == 0)
				Mix_PlayChannel(static_cast<int>(channels::enemy_deaths), enemyDeathSound, 0);
			break;
		case SoundID::projectileExplosion:
			if (Mix_Playing(static_cast<int>(channels::projectiles)) == 0)
				Mix_PlayChannel(static_cast<int>(channels::projectiles), projectileExplosionSound, 0);
			break;
		case SoundID::hoverUi:
			Mix_PlayChannel(static_cast<int>(channels::singular), hoverUi, 0);

			break;
		case SoundID::clickUi:
			Mix_PlayChannel(static_cast<int>(channels::singular), clickUi, 0);

			break;
		case SoundID::endWave:
			Mix_PlayChannel(static_cast<int>(channels::singular), endWave, 0);

			break;
		}
	}

	void AudioPlayer::PlayMusic() const
	{
		if (mute)
			return;
		if (Mix_PlayingMusic() == 0)
			Mix_PlayMusic(gameMusic, -1);
		else
			Mix_ResumeMusic();
	}

	void AudioPlayer::PauseMusic() const
	{
		if (mute)
			return;
		Mix_PauseMusic();
	}

	void AudioPlayer::StopMusic() const
	{
		Mix_FadeOutMusic(FADE_OUT_MUSIC);
	}

	void AudioPlayer::SwitchMute()
	{
		mute = !mute;
	}

	bool AudioPlayer::IsMuted() const
	{
		return mute;
	}
};
