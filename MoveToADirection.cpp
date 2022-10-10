#include "MoveToADirection.h"

MoveToADirection::MoveToADirection(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Collider* col, Callable* call, float speed) :
	Moveable(pos, col, speed),
	dir(dir),
	call(call)
{
	dir->normalize();
}

void MoveToADirection::Update(float deltaTime)
{

	Tmpl8::vec2 nextPos = { 0 };
	nextP = *pos;
	nextPos = (*dir) * speed * deltaTime;

	//add collision check

	nextP += nextPos;

	/*if (col->InGameScreen(nextP, *col)) //should check for some kind of bounds
		(*pos) = nextP;
	else {
		call->Call();
	}*/
	*pos = nextP;

}

MoveToADirection::~MoveToADirection()
{

}
