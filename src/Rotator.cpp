#include "Rotator.h"
#include "MathFunctions.h"
using namespace Tmpl8;
Rotator::Rotator(vec2* _pos, vec2* _dir, RotationVar* _rVar, unsigned int* _frame, MoveToADirection* _mover) :
	frame(_frame),
	pos(_pos),
	dir(_dir),
	rVar(_rVar),
	mover(_mover)

{

}

Rotator::Rotator() :
	frame(nullptr),
	pos(nullptr),
	dir(nullptr),
	rVar(nullptr),
	mover(nullptr)
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

void Rotator::Init(vec2* _pos, vec2* _dir, MoveToADirection* _mover)
{
	pos = _pos;
	dir = _dir;
	mover = _mover;
}


void Rotator::RotateToDirection(const vec2& newDir) const
{
	MathFunctions::RotateToDirection(newDir, *pos, *dir);
	if (frame)
		*frame = MathFunctions::RotateToDirectionFrames(*rVar, *dir);

}


void Rotator::Reflect(const vec2 normal) const
{
	mover->ReflectDirection(normal);
	RotateToDirection(*pos + *dir);
}
