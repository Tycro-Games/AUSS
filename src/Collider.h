#pragma once
#include "template.h"
struct Collider
{
	enum class Type {

		projectile,
		enemy,
		obstacle,
		nothing
	};
	Collider(Tmpl8::vec2 min, Tmpl8::vec2 max);
	Collider(Tmpl8::vec2 min, Tmpl8::vec2 max, Tmpl8::vec2* pos);
	Collider();
	Collider operator*(float multiplier);

	~Collider();
	Type type;
	Tmpl8::vec2 min, max;
	Tmpl8::vec2* pos;
	Collider* collision;
	bool toDeactivate = false;
	Collider At(const Tmpl8::vec2& offset) const;

	bool Collides(const Collider& col) const;

	static bool Collides(const Collider& a, const Collider& b);
	/// <summary>
	/// Checks if a is completely inside b
	/// </summary>
	/// <param name="a">small collider</param>
	/// <param name="b">big collider</param>
	/// <returns></returns>
	static bool Overlaps(const Collider& a, const Collider& b);
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
	static bool Contains(const Collider& a, const Tmpl8::vec2& b);

	static bool CollidesY(const Collider& a, const Collider& b);
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
	/// <param name="outputIntersection">is the returning point where the intersection happened</param>
	/// <param name="outputFraction">is the fraction that defines the point of intersection between the two points of the line</param>
	/// <returns></returns>
	static bool LineRectangleIntersection(const Tmpl8::vec2& v0, const Tmpl8::vec2& v1, const Collider& rect,
		Tmpl8::vec2& outputIntersection, float& outputFraction);

	static bool CollidesX(const Collider& a, const Collider& b);

	static bool InGameScreen(const Tmpl8::vec2& pos, const Collider& col)
	{

		return pos.x + col.min.x >= 0 && pos.y + col.min.y >= 0
			&& pos.x + col.max.x <= ScreenWidth - 1 && pos.y + col.max.y <= ScreenHeight - 1;
	}static bool InGameScreen(const Tmpl8::vec2& pos)
	{

		return pos.x >= 0 && pos.y >= 0
			&& pos.x <= ScreenWidth - 1 && pos.y <= ScreenHeight - 1;
	}
	static bool InGameBounds(const Collider& col);
	static bool InGameBounds(const Tmpl8::vec2& pos, const Collider& col);


	static Tmpl8::vec2 GetNormalEdgeScreen(const Tmpl8::vec2& pos, const Collider& col);

};


