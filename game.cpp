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
		player = new Player(new Sprite(new Surface("assets/sniper.tga"), 32), vec2(100, 200), 100);
		entities.push_back(player);
	}
	void Game::Shutdown()
	{
		delete player;
	}


	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		for (auto i : entities) {
			i->Update(screen);
		}

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
			player->mover.setUp();
		case(SDL_SCANCODE_S):
			player->mover.setDown();
		case(SDL_SCANCODE_D):
			player->mover.setRight();
		case(SDL_SCANCODE_A):
			player->mover.setLeft();
		default:
			break;
		}
	}
	void Game::KeyDown(SDL_Scancode key)
	{
		switch (key)
		{
		case(SDL_SCANCODE_W):
			player->mover.setUp(true);
		case(SDL_SCANCODE_S):
			player->mover.setDown(true);
		case(SDL_SCANCODE_D):
			player->mover.setRight(true);
		case(SDL_SCANCODE_A):
			player->mover.setLeft(true);
		default:
			break;
		}
	}
};