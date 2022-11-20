#include "Rotator.h"
#include "MathFunctions.h"
using namespace Tmpl8;
Rotator::Rotator(vec2* _pos, vec2* _dir, RotationVar* _rVar, unsigned int* _frame, MoveToADirection* _mover) :
	pos(_pos),
	dir(_dir),
	rVar(_rVar),
	mover(_mover),
	frame(_frame)

{

}

Rotator::Rotator() :
	pos(nullptr),
	dir(nullptr),
	rVar(nullptr),
	mover(nullptr),
	frame(0)
{
}

void Rotator::Init(vec2* _pos, vec2* _dir, RotationVar* _rVar, unsigned int* _frame, MoveToADirection* _mover)
{
	pos = _pos;
	dir = _dir;
	rVar = _rVar;
	frame = _frame;
	mover = _mover;
}


void Rotator::RotateToDirection(vec2 Pos)
{

	//rotate to the target dir
	int xPos = static_cast<int>(Pos.x);
	int yPos = static_cast<int>(Pos.y);
	int xpos = static_cast<int>(pos->x);
	int ypos = static_cast<int>(pos->y);

	MathFunctions::RotateTo(Pos.x, Pos.y, *pos, *dir);

	*frame = MathFunctions::RotateToDirectionFrames(*rVar, *dir);

}


void Rotator::Reflect(const vec2 normal)
{


	mover->OppositeDirection(normal);
	RotateToDirection(*pos + *dir);
}
