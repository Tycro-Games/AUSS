#include "MoveToADirectionEnemy.h"

MoveToADirectionEnemy::MoveToADirectionEnemy(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Collider* col, Callable* call, float speed)
	:
	MoveToADirection(pos,dir,col,call,speed)
{
}

MoveToADirectionEnemy::~MoveToADirectionEnemy()
{
}

void MoveToADirectionEnemy::Update(float deltaTime)
{
	Tmpl8::vec2 nextPos = { 0 };
	nextP = *pos;
	nextPos = (*dir) * speed * deltaTime;

	//add collision check

	nextP += nextPos;

	//some condition
	if (col->InGameScreen(nextP, *col))
		(*pos) = nextP;
	else {
		
	}
}
