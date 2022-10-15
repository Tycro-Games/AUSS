#include "Moveable.h"

Moveable::Moveable(Tmpl8::vec2* pos, Collider* col, float speed)
	: pos(pos),
	col(col),
	speed(speed)
{
}Moveable::Moveable(Tmpl8::vec2* pos)
	: pos(pos),
	col(NULL),
	speed(0)
{
}
void Moveable::SetSpeed(float s) {
	speed = s;
}
const float Moveable::GetSpeed() {
	return speed;
}
void Moveable::Translation(const Tmpl8::vec2 translation)
{
	*pos += translation;
}
Moveable::~Moveable()
{
}


