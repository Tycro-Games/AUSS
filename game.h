#pragma once

#include "Player.h"
#include "FollowCursor.h"
#include "Playbutton.h"
#include "Exitbutton.h"
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
		void SetTarget(Surface* surface) { screen = surface; }

		void Init();
		void AllocateMemory();
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
		void CheckButtons();
		void KeyUp(SDL_Scancode key);
		void KeyDown(SDL_Scancode key);

		static bool isPressingLeftMouse;
		//switching between game states
		enum GameState
		{

			mainMenu,
			game,
			paused,
			reset
		};
		static void ChangeGameState(GameState state);
		static GameState currentState;

		static dynamic_array<Moveable*> moveablesTile;
		static dynamic_array<Moveable*> moveablesPlayer;
		static Tilemap* tileMap;
		//collision detection
		static dynamic_array<Collider*> cols;
		static void AddCollider(Collider* col);
		static void AddMoveable(Moveable* col, dynamic_array<Moveable*>* vec = &moveablesTile);
		static void RemoveCollider(Collider* col);
		static void RemoveMoveable(Moveable* col, dynamic_array<Moveable*>* vec = &moveablesTile);
	private:
		Surface* screen;

		//MainMenu
		FollowCursor* cursor;
		Button* playButton;
		Button* exitButton;
		dynamic_array <Updateable*> updateablesUI;
		dynamic_array <Renderable*> renderablesUI;
		//actual game
		Player* player;
		Score score;
		EnemyWaveSpawner* enemySpawner;
		CollisionDetection* projectileDetection;
		MoveablePlayer* tileMovement;
		//update components
		dynamic_array<Updateable*> updateables;
		dynamic_array<Renderable*> renderables;

		//consts
		const float FIRE_SPEED_CHANGE = .1f;
		const Tmpl8::vec2 START_POS = Tmpl8::vec2(ScreenWidth / 2, ScreenHeight / 2);
		const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-33 / 2 - 5, -33 / 2 - 5);
		const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(33 / 2 + 5, 33 / 2 + 5);

	};

}; // namespace Tmpl8