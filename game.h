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
		Game();
		static Game& Get();

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
		std::vector<Collider*> colliders;
		void AddCollider(Collider* col);
		void AddMoveable(Moveable* col);
		void RemoveCollider(Collider* col);
		void RemoveMoveable(Moveable* col);
		void ChangeGameState(GameState state);
		GameState currentState;

		std::vector<Moveable*> moveablesTile;
		Tilemap tileMap;
	private:
		Surface* screen;

		//MainMenu
		FollowCursor* cursor;
		Button* playButton;
		Button* exitButton;
		std::vector <Updateable*> updateablesUI;
		std::vector <Renderable*> renderablesUI;
		//actual game
		Player* player;
		Score score;
		EnemyWaveSpawner* enemySpawner;
		CollisionDetection* projectileDetection;
		//update components
		std::vector<Updateable*> updateables;
		std::vector<Renderable*> renderables;

		//consts
		const float FIRE_SPEED_CHANGE = .1f;
		const Tmpl8::vec2 START_POS = Tmpl8::vec2(ScreenWidth / 2, ScreenHeight / 2);
		const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-33 / 2 - 5, -33 / 2 - 5);
		const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(33 / 2 + 5, 33 / 2 + 5);

	};

}; // namespace Tmpl8