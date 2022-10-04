#pragma once
#include "template.h"

struct Collider
{
public:
	Collider(Tmpl8::vec2 min, Tmpl8::vec2 max);
	Collider(Tmpl8::vec2 min, Tmpl8::vec2 max, Tmpl8::vec2* pos);
	Collider();
	Collider operator*(const float multiplier) {
		min *= multiplier;
		max *= multiplier;
		return Collider(min, max);
	}

	~Collider();
	Tmpl8::vec2 min, max;
	Tmpl8::vec2* pos;
	Collider* collision;
	bool toDeactivate = false;
	Collider At(const Tmpl8::vec2& offset) const {
		return Collider(min + offset, max + offset);
	}

	bool Collides(const Collider& col) {
		return Collides(this->At(*pos), col);
	}
	static bool Collides(const Collider& a, const Collider& b) {
		return a.min.x < b.max.x&& a.max.x>b.min.x &&
			a.min.y < b.max.y&& a.max.y>b.min.y;

	}static bool CollidesY(const Collider& a, const Collider& b) {
		return a.min.y < b.max.y&& a.max.y>b.min.y;

	}
	static bool CollidesX(const Collider& a, const Collider& b) {

		return a.min.x < b.max.x&& a.max.x>b.min.x;

	}
	static bool Collider::InGameScreen(Tmpl8::vec2& pos, Collider& col)
	{

		return pos.x + col.min.x > 0 && pos.y + col.min.y > 0
			&& pos.x + col.max.x < ScreenWidth - 1 && pos.y + col.max.y < ScreenHeight - 1;
	}
	static bool Collider::InGameScreen(Tmpl8::vec2& pos, Tmpl8::vec2& offset, Collider& col)
	{

		return pos.x + col.min.x > 0 + offset.x && pos.y + col.min.y > 0 + offset.y
			&& pos.x + col.max.x < ScreenWidth - 1 - offset.x && pos.y + col.max.y < ScreenHeight - 1 - offset.y;
	}
	static Tmpl8::vec2 Collider::GetNormalEdgeScreen(const Tmpl8::vec2& pos, const Collider& col)
	{
		Tmpl8::vec2 normal;
		if (pos.x + col.min.x <= 0 || pos.x + col.max.x >= ScreenWidth - 1)
			normal = Tmpl8::vec2(1, 0);
		else if (pos.y + col.min.y <= 0 || pos.y + col.max.y >= ScreenHeight - 1)
			normal = Tmpl8::vec2(0, 1);
		return normal;
	}
};


