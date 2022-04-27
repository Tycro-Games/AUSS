#pragma once
#include "Being.h"
#include "template.h"
class Player :public Being
{
public:
	Player(Tmpl8::Sprite* sprite, Tmpl8::vec2 pos, int hp);
	~Player();
	void Update(Tmpl8::Surface* screen);
	void Rotate(int x,int y);
private:
	const float angleSize = 360 / 32.0f;
	Tmpl8::vec2 dir={0,0};
};






