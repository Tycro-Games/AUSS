#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <iostream>
#include "template.h"

#include "MathFunctions.h"
namespace Tmpl8
{
	void Game::Init()
	{
		player = new Player(new Sprite(new Surface("assets/sniper.tga"), 32),
			new vec2(START_POS),
			new Collider(vec2(COL_MIN), vec2(COL_MAX)),
			100);
		updateables.push_back(player);
		updateables.push_back(player->GetMoveable());
		renderables.push_back(player);
	}
	void Game::Shutdown()
	{
		delete player;
	}


	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		for (auto i : renderables) {
			i->Render(screen);
		}
		for (auto i : updateables) {
			i->Update(deltaTime);
		}
		player->Shoot(isPressingLeftMouse);
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
		default:
			break;
		}
	}
};