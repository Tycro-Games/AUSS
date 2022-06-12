#include "Moveable.h"

Moveable::Moveable(Tmpl8::vec2* pos, Collider* col, float speed)
	: pos(pos),
	col(col),
	speed(speed)
{
}

Moveable::~Moveable()
{
}


