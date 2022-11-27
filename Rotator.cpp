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


void Rotator::RotateToDirection(const vec2& newDir)
{
	MathFunctions::RotateToDirection(newDir, *pos, *dir);

	*frame = MathFunctions::RotateToDirectionFrames(*rVar, *dir);

}


void Rotator::Reflect(const vec2 normal)
{


	mover->ReflectDirection(normal);
	RotateToDirection(*pos + *dir);
}
