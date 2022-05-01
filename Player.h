#pragma once
#include "Being.h"
#include "Moveable.h"
#include "Collider.h"

#include "template.h"
class Player :public Being
{
public:
	Player(Tmpl8::Sprite* sprite, Tmpl8::vec2* pos, int hp);
	~Player();
	void Render(Tmpl8::Surface* screen);
	void Update(float deltaTime);

	void Rotate(int x, int y);
	Moveable* mover;
	Collider col;

private:
	const float ANGLE_SIZE = 360 / 32.0f;
	const float OFFSET_SPRITE = 90.0f;
	const float SPRITE_OFFSET = 26;
	Tmpl8::vec2 dirToFace = { 0,0 };

};






