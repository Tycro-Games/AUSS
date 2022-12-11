#include "AudioPlayer.h"
namespace Tmpl8 {
	AudioPlayer::AudioPlayer()
	{
		menuMusic = Mix_LoadMUS("assets/Sounds&Music/music.wav");
		gameMusic = Mix_LoadMUS("assets/Sounds&Music/gameMusic.wav");
		playerShootingSound = Mix_LoadWAV("assets/Sounds&Music/playerShooting.wav");

	}

	AudioPlayer::~AudioPlayer()
	{
		//free memory
		Mix_FreeMusic(menuMusic);
		Mix_FreeMusic(gameMusic);

		Mix_FreeChunk(playerShootingSound);
	}
	void AudioPlayer::PlaySound()
	{
	}
	void AudioPlayer::PlayMusic()
	{
		if (Mix_PlayingMusic() == 0)
			Mix_PlayMusic(gameMusic, -1);
		else
			Mix_ResumeMusic();

	}
	void AudioPlayer::PauseMusic()
	{
		Mix_PauseMusic();
	}
};