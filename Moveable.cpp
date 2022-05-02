#include "Moveable.h"
Moveable::Moveable(Tmpl8::vec2* pos, Collider* col, float speed) :
	pos(pos),
	col(col),
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

	Tmpl8::vec2 nextPos = { 0 }, currentPos = *pos;
	if (up) {
		nextPos.y -= speed;
	}
	if (down) {
		nextPos.y += speed;
	}
	if (right) {
		nextPos.x += speed;
	}

	if (left) {
		nextPos.x -= speed;
	}
	//add collision check
	currentPos += nextPos;
	//screen check
	/*if (currentPos.x < 0)
		currentPos.x = 0;
	if (currentPos.x > ScreenWidth - 1)
		currentPos.x = ScreenWidth - 1;
	if (currentPos.y < 0)
		currentPos.y = 0;
	if (currentPos.y > ScreenHeight - 1)
		currentPos.y = ScreenHeight - 1;*/
	if (col->InGameScreen(currentPos)) {
		(*pos) = currentPos;
	}

}



