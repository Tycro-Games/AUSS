#pragma once

#include "Player.h"
#include "Cursor.h"
#include "Button.h"
#include "EnemyWaveSpawner.h"
#include "CollisionDetection.h"
#include "Tilemap.h"

#include <SDL_Scancode.h>

#include "Score.h"
#include "AudioID.h"
#include "FadingOut.h"
namespace Tmpl8 {
	class Surface;
	class AudioPlayer;
	class Game
	{

	public:
		Game();
		//this is the singleton pattern from this and Jeremiah: https://gameprogrammingpatterns.com/singleton.html
		static Game& Get();

		void SetTarget(Surface* surface) { screen = surface; }
		void SetAudio(AudioPlayer* audio) { audioPlayer = audio; }
		void Init();
		void Initializations();
		void ResetGame();
		void RemoveAllUpdateables();
		void AddInstancesToUpdates();

		static void AssignSubject(Subject& subject, Observer& observer);
		static void RemoveSubject(Subject& subject, Observer& observer);


		//SDL functions
		static void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button);
		void MouseDown(int button);
		void MouseMove(int x, int y);
		void CheckButtons(int x, int y);
		void KeyUp(SDL_Scancode key);
		void KeyDown(SDL_Scancode key);
		//audio playing
		void PlaySound(SoundID id) const;
		void PlayMusic() const;
		void StopMusic() const;
		void ResetMusic() const;
		bool isPressingLeftMouse = false;
		//switching between game states
		enum class GameState
		{

			mainMenu,
			game,
			paused,
			reset
		};
		//collision detection
		void AddCollider(Collider* col);
		void AddMoveable(Moveable* col);
		void RemoveCollider(Collider* col);
		void RemoveMoveable(Moveable* col);
		void ChangeGameState(GameState state);
		//getters
		const Tilemap& getTilemap();
		GameState getCurrentState() const;
		const Player& getPlayer();
		//this needs to be sorted for the collision checking so no const
		std::vector<Collider*>& getColliders();

	private:
		Surface* screen;
		AudioPlayer* audioPlayer;

		GameState currentState;
		Tilemap tileMap;
		void ResumeGame();
		void ExitGame() const;
		void MuteSound();
		bool changedVolumeButtons = false;
		std::vector<Collider*> colliders;
		std::vector<Moveable*> moveablesTile;
		//MainMenu
		Cursor cursor;
		Button playButton;
		Button exitButton;
		Button muteButton;
		Button volumeButton;
		FadingOut fadeInOut;
		//actual game
		Player player;
		Score score;
		EnemyWaveSpawner waveSpawner;
		CollisionDetection projectileDetection;
		//update components
		std::vector<Updateable*> updateables;
		std::vector<Renderable*> renderables;

		//consts
		const float FIRE_SPEED_CHANGE = .1f;

		//code for capping the frame rate
		/*const int SCREEN_FPS = 100;
		const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
		int countedFrames = 0;
		float currentTime = 0.0f;*/
	};

}; // namespace Tmpl8