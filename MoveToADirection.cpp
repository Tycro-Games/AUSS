#include "MoveToADirection.h"

MoveToADirection::MoveToADirection(Tmpl8::vec2* pos, Tmpl8::vec2 dir, Collider* col, float speed) :
	Moveable(pos, col, speed),
	dir(dir)
{
}

void MoveToADirection::Update(float deltaTime)
{
	Tmpl8::vec2 nextPos = { 0 }, currentPos = *pos;
	nextPos = dir * speed;
	//add collision check
	currentPos += nextPos;

	(*pos) = currentPos;

}

MoveToADirection::~MoveToADirection()
{
}
