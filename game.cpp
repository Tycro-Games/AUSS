#include "game.h"
#include "surface.h"
#include <iostream>
#include "template.h"

#include "MathFunctions.h"
#include "MergeSort.h"
namespace Tmpl8
{
	bool Game::isPressingLeftMouse;
	Game::GameState Game::currentState;
	//vector<float> a(19);
	void Game::Init()
	{
#ifdef _RELEASE
		currentState = mainMenu;
#endif
#ifdef _DEBUG
		currentState = game;
#endif

		player = (new Player(new Sprite(new Surface("assets/sniper.tga"), 32),
			new vec2(START_POS),
			new Collider(vec2(COL_MIN), vec2(COL_MAX)),
			100));
		cursor = (new FollowCursor(new Sprite(new Surface("assets/target.tga"), 1)));


		playButton = new PlayButton(new Sprite(new Surface("assets/Play_Idle.png"), 1), new Tmpl8::vec2(ScreenWidth / 2, ScreenHeight / 2),
			cursor->GetCollider(),
			new Sprite(new Tmpl8::Surface("assets/Play_Idle.png"), 1),
			new Sprite(new Tmpl8::Surface("assets/Play_Pushed.png"), 1));

		exitButton = new ExitButton(new Sprite(new Surface("assets/Cross_Idle.png"), 1), new Tmpl8::vec2(ScreenWidth / 2, ScreenHeight / 2 + 64),
			cursor->GetCollider(),
			new Sprite(new Tmpl8::Surface("assets/Cross_Idle.png"), 1),
			new Sprite(new Tmpl8::Surface("assets/Cross_Pushed.png"), 1));


		AddInstancesToUpdates();
	}
	void Game::AddInstancesToUpdates()
	{
		updateablesUI.push_back(playButton);
		renderablesUI.push_back(playButton);

		updateablesUI.push_back(exitButton);
		renderablesUI.push_back(exitButton);

		updateables.push_back(player);
		updateables.push_back(player->GetMoveable());
		renderables.push_back(player);

	}
	void Game::Shutdown()
	{
		delete playButton;
		delete exitButton;
		delete player;
		delete cursor;

	}


	void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f; //make time into seconds
		screen->Clear(0);

		switch (currentState)
		{
		case(game):
			for (int i = 0; i < renderables.getCount(); i++)
				renderables[i]->Render(screen);
			for (int i = 0; i < updateables.getCount(); i++)
				updateables[i]->Update(deltaTime);


			player->Shoot(isPressingLeftMouse);
			break;
		case(mainMenu):
			//update main menu stuff;
			for (int i = 0; i < renderablesUI.getCount(); i++)
				renderablesUI[i]->Render(screen);
			for (int i = 0; i < updateablesUI.getCount(); i++)
				updateablesUI[i]->Update(deltaTime);

			break;
		case(paused):
			//pause stuff menu
			for (int i = 0; i < renderablesUI.getCount(); i++)
				renderablesUI[i]->Render(screen);
			for (int i = 0; i < updateablesUI.getCount(); i++)
				updateablesUI[i]->Update(deltaTime);
			break;
		default:
			break;
		}
		cursor->Render(screen);
	}


	void Game::MouseUp(int button)
	{
		isPressingLeftMouse = false;
	}
	void Game::MouseDown(int button)
	{
		isPressingLeftMouse = true;
	}
	void Game::MouseMove(int x, int y)
	{
		cursor->ChangePosition(x, y);
		player->Rotate(x, y);
		if (currentState == game)
			return;
		//check buttons only if the mouse is moving
		CheckButtons();
	}
	void Game::CheckButtons()
	{
		playButton->ChangeSprite();
		exitButton->ChangeSprite();
	}
	void Game::KeyUp(SDL_Scancode key)
	{
		switch (key)
		{
		case(SDL_SCANCODE_W):
			player->GetMoveable()->setUp();

			break;
		case(SDL_SCANCODE_S):
			player->GetMoveable()->setDown();

			break;
		case(SDL_SCANCODE_D):
			player->GetMoveable()->setRight();

			break;
		case(SDL_SCANCODE_A):
			player->GetMoveable()->setLeft();

			break;

		default:
			break;
		}
	}
	void Game::KeyDown(SDL_Scancode key)
	{
		switch (key)
		{
		case SDL_SCANCODE_W:
			player->GetMoveable()->setUp(true);
			player->Rotate(cursor->pos->x, cursor->pos->y);
			break;
		case SDL_SCANCODE_S:
			player->GetMoveable()->setDown(true);
			player->Rotate(cursor->pos->x, cursor->pos->y);
			break;
		case SDL_SCANCODE_D:
			player->GetMoveable()->setRight(true);
			player->Rotate(cursor->pos->x, cursor->pos->y);
			break;
		case SDL_SCANCODE_A:
			player->GetMoveable()->setLeft(true);
			player->Rotate(cursor->pos->x, cursor->pos->y);
			break;
			//dash
		case SDL_SCANCODE_F:
			player->GetMoveable()->startDash();
			break;
			//firerate
		case SDL_SCANCODE_UP:
			player->GetSpawner()->ChangeFireSpeed(FIRE_SPEED_CHANGE);
			break;
		case SDL_SCANCODE_DOWN:
			player->GetSpawner()->ChangeFireSpeed(-FIRE_SPEED_CHANGE);
			break;
		case SDL_SCANCODE_ESCAPE:
			if (currentState == game) {
				ChangeGameState(paused);
				//reset button sprites
				playButton->Init();
				exitButton->Init();
				//check if the mouse is already hovering over them
				CheckButtons();
			}
			break;
		default:
			break;
		}
	}
	void Game::ChangeGameState(GameState state)
	{
		currentState = state;
	}
};