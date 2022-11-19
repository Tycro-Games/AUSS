#pragma once

#include "Player.h"
#include "Cursor.h"
#include "Button.h"
#include "EnemyWaveSpawner.h"
#include "CollisionDetection.h"
#include "Tilemap.h"

#include <SDL_Scancode.h>
#include "Score.h"
namespace Tmpl8 {

	class Surface;
	class Game
	{
	public:
		Game();
		static Game& Get();

		void SetTarget(Surface* surface) { screen = surface; }
		void Init();
		void Initializations();
		void ResetGame();
		void RemoveAllUpdateables();
		void AddInstancesToUpdates();

		void AssignSubject(Subject& subject, Observer& observer);


		//SDL functions
		void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button);
		void MouseDown(int button);
		void MouseMove(int x, int y);
		void CheckButtons(int x, int y);
		void KeyUp(SDL_Scancode key);
		void KeyDown(SDL_Scancode key);

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
		const GameState getCurrentState();
		const Player& getPlayer();
		//this needs to be sorted for the collision checking so no const
		std::vector<Collider*>& getColliders();

	private:
		Surface* screen;

		GameState currentState;
		Tilemap tileMap;
		void ResumeGame();
		void ExitGame();

		std::vector<Collider*> colliders;
		std::vector<Moveable*> moveablesTile;
		//MainMenu
		Cursor cursor;
		Button playButton;
		Button exitButton;
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


	};

}; // namespace Tmpl8