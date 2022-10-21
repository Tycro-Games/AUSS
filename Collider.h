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
	}
	/// <summary>
	/// Checks if a is completely inside b
	/// </summary>
	/// <param name="a">small collider</param>
	/// <param name="b">big collider</param>
	/// <returns></returns>
	static bool Overlaps(const Collider& a, const Collider& b) {

		return a.min.x > b.min.x && a.min.y > b.min.y
			&& a.max.x < b.max.x&& a.max.y < b.max.y;

	}
	/// <summary>
	/// checks if the vector it is inside the collider
	/// </summary>
	/// <param name="a"> collider to check</param>
	/// <param name="b">the vector that may be inside the collider</param>
	/// <returns></returns>
	static bool Contains(const Collider& a, const Tmpl8::vec2& b) {

		return a.min.x + a.pos->x < b.x&& a.min.y + a.pos->y < b.y
			&& b.x < a.max.x + a.pos->x && b.y < a.max.y + a.pos->y;

	}static bool CollidesY(const Collider& a, const Collider& b) {
		return a.min.y < b.max.y&& a.max.y>b.min.y;

	}
	static bool CollidesX(const Collider& a, const Collider& b) {

		return a.min.x < b.max.x&& a.max.x>b.min.x;

	}
	static bool Collider::TileMapInGameScreen(Tmpl8::vec2& pos, Collider& col)
	{

		return pos.x + col.min.x >= 0 && pos.y + col.min.y >= 0
			&& pos.x + col.max.x <= ScreenWidth - 1 && pos.y + col.max.y <= ScreenHeight - 1;
	}
	static bool Collider::InGameBounds(Collider& col);
	static bool Collider::InGameBounds(Tmpl8::vec2& pos, Collider& col);


	static Tmpl8::vec2 Collider::GetNormalEdgeScreen(const Tmpl8::vec2& pos, const Collider& col);




};


