#include "AudioPlayer.h"

namespace Tmpl8 {
	AudioPlayer::AudioPlayer()
	{
		menuMusic = Mix_LoadMUS("assets/Sounds&Music/music.wav");
		gameMusic = Mix_LoadMUS("assets/Sounds&Music/gameMusic.wav");
		playerShootingSound = Mix_LoadWAV("assets/Sounds&Music/playerShoot.wav");

	}

	AudioPlayer::~AudioPlayer()
	{
		//free memory
		Mix_FreeMusic(menuMusic);
		Mix_FreeMusic(gameMusic);

		Mix_FreeChunk(playerShootingSound);
	}
	void AudioPlayer::PlaySound(const SoundID id) const
	{
		if (mute)
			return;
		switch (id)
		{
		case SoundID::playerShooting:
			Mix_PlayChannel(static_cast<int>(channels::shootings), playerShootingSound, 0);
			break;
		case SoundID::playerDamage:  // NOLINT(bugprone-branch-clone)
			break;
		case SoundID::playerDeath:
			break;
		case SoundID::playerDash:
			break;
		case SoundID::enemyHit:
			break;
		case SoundID::enemyMeleeAtack:
			break;
		case SoundID::enemyShoot:
			break;
		case SoundID::enemyDeath:
			break;
		case SoundID::explosion:
			break;
		case SoundID::hoverUI:
			break;
		case SoundID::clickUI:
			break;
		case SoundID::endWave:
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