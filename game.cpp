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
		player = new Player(new Sprite(new Surface("assets/sniper.tga"), 32), new vec2(100, 200), 100);
		updateables.push_back(player);
		updateables.push_back(player->mover);
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
			player->mover->setUp();
			break;
		case(SDL_SCANCODE_S):
			player->mover->setDown();
			break;
		case(SDL_SCANCODE_D):
			player->mover->setRight();
			break;
		case(SDL_SCANCODE_A):
			player->mover->setLeft();
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
			player->mover->setUp(true);
			break;
		case SDL_SCANCODE_S:
			player->mover->setDown(true);
			break;
		case SDL_SCANCODE_D:
			player->mover->setRight(true);
			break;
		case SDL_SCANCODE_A:
			player->mover->setLeft(true);
			break;
		default:
			break;
		}
	}
};