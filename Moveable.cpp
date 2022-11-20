#include "Moveable.h"
using namespace Tmpl8;
Moveable::Moveable(vec2* _pos, Collider* _collider, float _speed)
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
	collider(nullptr),
	pos(nullptr),
	speed(0)
{
}
void Moveable::Init(vec2* _pos, Collider* _col, float speed)
{
	pos = _pos;
	collider = _col;
	SetSpeed(speed);

}
void Moveable::Init(vec2* _pos)
{
	pos = _pos;
}
void Moveable::SetSpeed(float s) {
	speed = s;
}
const float Moveable::GetSpeed() {
	return speed;
}
void Moveable::Translation(const vec2 translation)
{
	*pos += translation;
}
Moveable::~Moveable()
{
}


