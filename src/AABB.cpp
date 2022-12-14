#include "AABB.h"

bool AABB::IsColliding(const Tmpl8::vec2& pos) const
{
	return pos.x > min.x && pos.x < max.x&&
		pos.y > min.y && pos.y < max.y;
}
