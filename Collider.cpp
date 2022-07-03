#include "Collider.h"

Collider::Collider(Tmpl8::vec2 min, Tmpl8::vec2 max) :
	min(min),
	max(max)
{
}

Collider::Collider() :
	min(0),
	max(0)
{
}

Collider::~Collider()
{
}


