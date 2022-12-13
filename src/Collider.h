#pragma once
#include "template.h"
struct Collider
{
public:
	enum class Type {

		Projectile,
		Enemy,
		Obstacle,
		Nothing
	};
	Collider(Tmpl8::vec2 min, Tmpl8::vec2 max);
	Collider(Tmpl8::vec2 min, Tmpl8::vec2 max, Tmpl8::vec2* pos);
	Collider();
	Collider operator*(const float multiplier) {
		min *= multiplier;
		max *= multiplier;
		return Collider(min, max);
	}

	~Collider() = default;
	Type type;
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
		return a.min.x <= b.max.x && a.max.x >= b.min.x &&
			a.min.y <= b.max.y && a.max.y >= b.min.y;
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
	/// Gets the normal from the collider source to the obstacle
	///based on https://gamedev.stackexchange.com/questions/136073/how-does-one-calculate-the-surface-normal-in-2d-collisions
	/// </summary>
	/// <param name="obstacle"> is colliding with source</param>
	/// <param name="source"> will have the normal point to it</param>
	/// <returns></returns>
	static Tmpl8::vec2 GetNormal(const Collider& obstacle, const Collider& source);
	/// <summary>
	/// checks if the vector it is inside the collider
	/// </summary>
	/// <param name="a"> collider to check</param>
	/// <param name="b">the point that may be inside the collider</param>
	/// <returns></returns>
	static bool Contains(const Collider& a, Tmpl8::vec2& b) {
		/*float xP = round(b.x);
		float yP = round(b.y);
		float Left = round(a.min.x + a.pos->x);
		float Right = round(a.max.x + a.pos->x);
		float Up = round(a.min.y + a.pos->y);
		float Down = round(a.max.y + a.pos->y);
		return xP >= Left && yP >= Up
			&& xP <= Right - 1 && yP <= Down - 1;*/
		return a.min.x + a.pos->x < b.x&& a.min.y + a.pos->y < b.y
			&& b.x < a.max.x + a.pos->x && b.y < a.max.y + a.pos->y;
	}
	static bool CollidesY(const Collider& a, const Collider& b) {
		return a.min.y < b.max.y&& a.max.y > b.min.y;

	}
	//based on https://www.youtube.com/watch?v=3vONlLYtHUE&t=0s

	/// <summary>
	/// Clips the line with the rectangle on one axis trying to determine the interval where the intersection happens
	/// </summary>
	/// <param name="clipX">is the flag for choosing the axis</param>
	/// <param name="rectangle">is collider that we are checking</param>
	/// <param name="v0">is the start of the lin</param>
	/// <param name="v1">is the end of the line</param>
	/// <param name="low">is the lower part of the interval</param>
	/// <param name="high">is the higher part of the interval</param>
	/// <returns></returns>
	static bool ClipLineOnOneAxis(bool clipX, const Collider& rectangle, const Tmpl8::vec2& v0, const Tmpl8::vec2& v1, float& low, float& high);
	/// <summary>
	/// Determines if the line is intersecting with the box
	/// </summary>
	/// <param name="v0">is the start of the line</param>
	/// <param name="v1">is the end of the line</param>
	/// <param name="rect">is collider that we are checking</param>
	/// <param name="outputPointOfIntersection">is the returning point where the intersection happened</param>
	/// <param name="outpuFraction">is the fraction that defines the point of intersection between the two points of the line</param>
	/// <returns></returns>
	static bool LineRectangleIntersection(const Tmpl8::vec2& v0, const Tmpl8::vec2& v1, const Collider& rect, Tmpl8::vec2& outputIntersection, float& outpuFraction);

	static bool CollidesX(const Collider& a, const Collider& b) {

		return a.min.x < b.max.x&& a.max.x > b.min.x;

	}
	static bool Collider::InGameScreen(const Tmpl8::vec2& pos, const Collider& col)
	{

		return pos.x + col.min.x >= 0 && pos.y + col.min.y >= 0
			&& pos.x + col.max.x <= ScreenWidth - 1 && pos.y + col.max.y <= ScreenHeight - 1;
	}static bool Collider::InGameScreen(const Tmpl8::vec2& pos)
	{

		return pos.x >= 0 && pos.y >= 0
			&& pos.x <= ScreenWidth - 1 && pos.y <= ScreenHeight - 1;
	}
	static bool Collider::InGameBounds(Collider& col);
	static bool Collider::InGameBounds(const Tmpl8::vec2& pos, Collider& col);


	static Tmpl8::vec2 Collider::GetNormalEdgeScreen(const Tmpl8::vec2& pos, const Collider& col);

};

