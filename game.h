#pragma once

#include "Player.h"

#include "FollowCursor.h"
#include "Playbutton.h"
#include "Exitbutton.h"

#include <SDL_Scancode.h>

namespace Tmpl8 {

	class Surface;
	class Game
	{
	public:
		void SetTarget(Surface* surface) { screen = surface; }

		void Init();
		void AddInstancesToUpdates();
		void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button);
		void MouseDown(int button);
		void MouseMove(int x, int y);
		void KeyUp(SDL_Scancode key);
		void KeyDown(SDL_Scancode key);

		static bool isPressingLeftMouse;
		enum GameState
		{

			mainMenu,
			game,
			paused
		};
		static void ChangeGameState(GameState state);
		static GameState currentState;
	private:


		Surface* screen;

		FollowCursor* cursor;
		//MainMenu
		Button* playButton;
		Button* exitButton;
		vector <Updateable*> updateablesUI;
		vector <Renderable*> renderablesUI;
		//actual game
		Player* player;
		vector<Updateable*> updateables;
		vector<Renderable*> renderables;



		const float FIRE_SPEED_CHANGE = .1f;
		const Tmpl8::vec2 START_POS = Tmpl8::vec2(450, 400);
		const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(0, 0);
		const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(26, 26);

	};

}; // namespace Tmpl8