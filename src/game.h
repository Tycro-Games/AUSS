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

namespace Tmpl8
{
	class Surface;
	class AudioPlayer;

	class Game
	{
	public:
		Game();
		~Game();
		//this is the singleton pattern from this and Jeremiah: https://gameprogrammingpatterns.com/singleton.html
		static Game& Get();
		//initializations
		void Init();

		//switching between game states
		enum class GameState
		{
			mainMenu,
			game,
			paused,
			reset
		};

		//getters
		GameState getCurrentState() const;
		const Tilemap& getTilemap();
		const Player& getPlayer();
		//setters
		void SetTarget(Surface* surface) { screen = surface; }
		void SetAudio(AudioPlayer* audio) { audioPlayer = audio; }


		//observer functions
		static void AssignSubject(Subject& subject, Observer& observer);
		static void RemoveSubject(Subject& subject, Observer& observer);


		//SDL functions
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
		//collision detection
		/**
		 * \brief Adds a collider to the detect collision list.
		 */
		void AddCollider(Collider* col);
		/**
		 * \brief Removes a collider to the detect collision list.
		 */
		void RemoveCollider(Collider* col);
		/**
		 * \brief Adds an instance that should be moved regardless of the screen.
		 */
		void AddMoveable(Moveable* col);
		/**
		 * \brief Removes an instance that should be moved regardless of the screen.
		 */
		void RemoveMoveable(Moveable* col);
		/**
		 * \brief Changes the current state to the parameter.
		 * \param state To be changed into.
		 */
		void ChangeGameState(GameState state);
		//this needs to be sorted by the collision detection
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
		std::vector<Collider*> colliders;
		std::vector<Moveable*> moveablesTile;
		//MainMenu
		Button playButton;
		Button exitButton;
		//Sound changing
		Button muteButton;
		Button volumeButton;
		bool changedVolumeButtons = false;
		void MuteSound();
		//reset or pause game
		FadingOut fadeInOut;
		void ResumeGame();
		void ExitGame() const;
		//actual game
		Cursor cursor;
		Player player;
		Score score;
		/**
		 * \brief Spawner of enemy waves.
		 */
		EnemyWaveSpawner waveSpawner;
		/**
		 * \brief Collision detection between player projectiles and enemies.
		 */
		CollisionDetection projectileDetection;
		//update vectors for rendering and updates
		std::vector<Updateable*> updateables;
		std::vector<Renderable*> renderables;
	};
}; // namespace Tmpl8
