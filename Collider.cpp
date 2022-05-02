#include "Collider.h"

Collider::Collider(Tmpl8::vec2 min, Tmpl8::vec2 max) :
	min(min),
	max(max)
{
}

Collider::~Collider()
{
}

bool Collider::InGameScreen(Tmpl8::vec2& pos)
{

	return pos.x + min.x > 0 && pos.y + min.y > 0
		&& pos.x + max.x < ScreenWidth - 1 && pos.y + max.y < ScreenHeight - 1;
}
