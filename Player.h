#pragma once
#include "Being.h"
#include "template.h"
class Player :public Being
{
public:
	Player(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, int hp);
	~Player();
	void Update(Tmpl8::Surface* screen);
	void Rotate(int x, int y);
private:
	const float ANGLE_SIZE = 360 / 32.0f;
	const float OFFSET_SPRITE = 90.0f;
	Tmpl8::vec2 dir = { 0,0 };
};






