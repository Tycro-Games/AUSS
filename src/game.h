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
		//setters
		void SetTarget(Surface* surface) { screen = surface; }
		void SetAudio(AudioPlayer* audio) { audioPlayer = audio; }
		//initializations
		void Init();


		//observer functions
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
		bool isPressingLeftMouse = false;
		//audio playing
		void PlaySound(SoundID id) const;
		void PlayMusic() const;
		void StopMusic() const;
		void ResetMusic() const;
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
		//auxialiary methods
		/**
		 * \brief resets the game to the initial state
		 */
		void ResetGame();
		void Initializations();
		/**
		 * \brief removes the objects from the update lists
		 */
		void RemoveAllUpdateables();
		/**
		 * \brief adds objects to lists that update them
		 */
		void AddInstancesToUpdates();
		Surface* screen;
		AudioPlayer* audioPlayer;

		GameState currentState;
		Tilemap tileMap;
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
		void ResumeGame();
		void ExitGame() const;
		void MuteSound();
		//actual game
		Player player;
		Score score;
		EnemyWaveSpawner waveSpawner;
		CollisionDetection projectileDetection;
		//update vectors
		std::vector<Updateable*> updateables;
		std::vector<Renderable*> renderables;

	};

}; // namespace Tmpl8