#pragma once

//jeremiahs' review was the source https://youtu.be/qbOHI0CRzD4?t=2611
#include "template.h"
//lightweight version of collider for axis aligned bounding box
struct AABB
{
	AABB(const Tmpl8::vec2& min, const Tmpl8::vec2& max)
		:
		min{ min },
		max{ max }
	{
	}
	AABB()
		:
		min{ 0.0f },
		max{ 0.0f }
	{
	}
	//could also derive from an tile based on its position

	bool isColliding(const Tmpl8::vec2& pos);
	Tmpl8::vec2 min;
	Tmpl8::vec2 max;
};

