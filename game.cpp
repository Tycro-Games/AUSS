#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <iostream>
#include "template.h"
#include "vector.h"
#include "MathFunctions.h"
#include "MergeSort.h"
namespace Tmpl8
{
	vector<float> a(19);
	void Game::Init()
	{

		player = (new Player(new Sprite(new Surface("Build/assets/sniper.tga"), 32),
			new vec2(START_POS),
			new Collider(vec2(COL_MIN), vec2(COL_MAX)),
			100));
		cursor = (new FollowCursor(new Sprite(new Surface("Build/assets/target.tga"), 1)));

		playButton = new Button(new Sprite(new Surface("Build/assets/Play_Idle.png"), 1));
		a.push_back(10);
		a.push_back(2);
		a.push_back(1);
		a.push_back(3);
		a.push_back(11);
		a.push_back(5);
		a.push_back(7);
		a.push_back(7.8f);
		a.push_back(8);
		a.push_back(9.1f);
		a.push_back(12);
		MergeSort<float> q(&a);

		q.Sort(0, a.getCount() - 1);


		q.Sort(0, a.getCount() - 1);
		a.print();
		AddInstancesToUpdates();
	}
	void Game::AddInstancesToUpdates()
	{


		updateables.push_back(player);
		updateables.push_back(player->GetMoveable());
		renderables.push_back(player);
	}
	void Game::Shutdown()
	{
		delete playButton;
		delete player;
		delete cursor;
	}


	void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f; //make time into seconds
		screen->Clear(0);

		switch (state)
		{
		case(game):
			for (auto i : renderables) {
				i->Render(screen);
			}

			for (auto i : updateables) {
				i->Update(deltaTime);
			}
			player->Shoot(isPressingLeftMouse);
			break;
		case(mainMenu):
			//update main menu stuff;
			playButton->Update(deltaTime);
			playButton->Render(screen);
			break;
		case(paused):
			//pause stuff menu
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
			break;
		case SDL_SCANCODE_S:
			player->GetMoveable()->setDown(true);
			break;
		case SDL_SCANCODE_D:
			player->GetMoveable()->setRight(true);
			break;
		case SDL_SCANCODE_A:
			player->GetMoveable()->setLeft(true);
			break;
			//firerate
		case SDL_SCANCODE_UP:
			player->GetSpawner()->ChangeFireSpeed(FIRE_SPEED_CHANGE);
			break;
		case SDL_SCANCODE_DOWN:
			player->GetSpawner()->ChangeFireSpeed(-FIRE_SPEED_CHANGE);
			break;
		default:
			break;
		}
	}
};