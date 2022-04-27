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
	}
	void Game::Shutdown()
	{
		delete player;
	}


	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		player->Update(screen);

	}
	void Game::MouseMove(int x, int y)
	{
		player->Rotate(x, y);
	}
};