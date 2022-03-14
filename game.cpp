#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <iostream>
#include "template.h"

namespace Tmpl8
{
	static Sprite sniperSprite(new Surface("assets/sniper.tga"), 32);
	static int frame = 0;
	const float angleSize = 360 / 32.0f;
	vec2 dir;
	void Game::Init()
	{
	}
	void Game::Shutdown()
	{
	}
	void Game::SetSprite()
	{
		sniperSprite.SetFrame(frame);
		sniperSprite.Draw(screen, 100, 200);

	}

	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		SetSprite();

	}
	void Game::MouseMove(int x, int y)
	{
		dir.x = x - 100;
		dir.y = y - 200;
		dir.normalize();


		float angle = atan2(dir.y, dir.x);//return angle in radians

		angle *= (180 / PI);//convert to angles from radians
		if (angle < 0) //convert to positive angles
		{
			angle = 360 - (-angle);
		}
		angle += 90;//offset for the image
		angle = fmod(angle, 360);
		frame = angle / angleSize;
	}
};