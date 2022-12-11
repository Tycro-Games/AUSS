#include "AudioPlayer.h"
AudioPlayer::AudioPlayer()
{
	//init mixer audio
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);


	music = Mix_LoadMUS("assets/Sounds&Music/music.wav");
	playerShootingSound = Mix_LoadWAV("assets/Sounds&Music/playerShooting.wav");
	//-1 means loop 
	Mix_PlayMusic(music, -1);
}

AudioPlayer::~AudioPlayer()
{
	//free memory
	Mix_FreeMusic(music);

	Mix_FreeChunk(playerShootingSound);
	Mix_Quit();
}
void AudioPlayer::PlaySound()
{
}
