// ReSharper disable All
#include "Collider.h"
#include "game.h"
using namespace Tmpl8;

Collider::Collider(vec2 min, vec2 max) :
	min(min),
	max(max),
	pos(nullptr),
	collision()
{
	type = Type::nothing;
}

Collider::Collider(vec2 min, vec2 max, vec2* pos) :
	min(min),
	max(max),
	pos(pos),
	collision()
{
	type = Type::nothing;
}

Collider::Collider() :
	min(0),
	max(0),
	pos(nullptr),
	collision()
{
	type = Type::nothing;
}

Collider Collider::operator*(const float multiplier)
{
	min *= multiplier;
	max *= multiplier;
	return { min, max };
}

Collider Collider::At(const Tmpl8::vec2& offset) const
{
	return { min + offset, max + offset };
}

bool Collider::Collides(const Collider& collider) const
{
	return Collides(this->At(*pos), collider);
}

bool Collider::Collides(const Collider& a, const Collider& b)
{
	return a.min.x <= b.max.x && a.max.x >= b.min.x &&
		a.min.y <= b.max.y && a.max.y >= b.min.y;
}
