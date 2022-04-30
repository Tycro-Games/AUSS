#include "Moveable.h"
#include <iostream>
Moveable::Moveable(Tmpl8::vec2 pos, float speed) :
	pos(pos),
	speed(speed)
{

}

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

void Moveable::Move()
{
	Tmpl8::vec2 nextPos = { 0,0 };
	if (up) {
		nextPos.y++;
	}
	if (down) {
		nextPos.y--;
	}if (right) {
		nextPos.x++;
	}if (left) {
		nextPos.x--;
	}
}



