#include "Collider.h"

Collider::Collider(Tmpl8::vec2 min, Tmpl8::vec2 max) :
	min(min),
	max(max),
	pos(0)
{
}

Collider::Collider(Tmpl8::vec2 min, Tmpl8::vec2 max, Tmpl8::vec2* pos) :
	min(min),
	max(max),
	pos(pos)
{
}

Collider::Collider() :
	min(0),
	max(0),
	pos(0)
{
}

Collider::~Collider()
{
}


