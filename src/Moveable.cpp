#include "Moveable.h"
using namespace Tmpl8;

Moveable::Moveable(vec2* _pos, Collider* _collider, const float _speed)
	: pos(_pos),
	collider(_collider),
	speed(_speed)
{
}

Moveable::Moveable(vec2* _pos)
	: pos(_pos),
	collider(nullptr),
	speed(0)
{
}

Moveable::Moveable() :
	pos(nullptr),
	collider(nullptr),
	speed(0)
{
}

void Moveable::Init(vec2* _pos, Collider* _col, const float _speed)
{
	pos = _pos;
	collider = _col;
	SetSpeed(_speed);
}

void Moveable::Init(vec2* _pos)
{
	pos = _pos;
}

void Moveable::Update(float deltaTime)
{
}

void Moveable::SetSpeed(const float s)
{
	speed = s;
}

float Moveable::GetSpeed() const
{
	return speed;
}

void Moveable::Translation(const vec2 translation)
{
	*pos += translation;
}
