#include "AABB.h"

bool AABB::isColliding(const Tmpl8::vec2& pos)
{
	return pos.x > min.x && pos.x < max.x&&
		pos.y > min.y && pos.y < max.y;
}
