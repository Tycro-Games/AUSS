#include "Moveable.h"
#include <iostream>
Moveable::Moveable(Tmpl8::vec2* pos, float speed) :
	pos(pos),
	speed(speed)
{}

Moveable::~Moveable()
{
}

void Moveable::setUp(bool val)
{
	up = val;
}

void Moveable::setDown(bool val)
{
	down = val;
}

void Moveable::setRight(bool val)
{
	right = val;
}

void Moveable::setLeft(bool val)
{
	left = val;
}


void Moveable::Update(float deltaTime)
{
	Tmpl8::vec2 nextPos = { 0 };
	if (up) {
		nextPos.y -= speed * deltaTime;
	}
	if (down) {
		nextPos.y += speed * deltaTime;
	}
	if (right) {
		nextPos.x += speed * deltaTime;
	}

	if (left) {
		nextPos.x -= speed * deltaTime;
	}
	//add collision check
	(*pos) += nextPos;
}



