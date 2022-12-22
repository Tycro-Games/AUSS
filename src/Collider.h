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

	Collider();
	Collider(Tmpl8::vec2 min, Tmpl8::vec2 max);
	Collider(Tmpl8::vec2 min, Tmpl8::vec2 max, Tmpl8::vec2* pos);

	~Collider() = default;

	Collider operator*(float multiplier);

	Tmpl8::vec2 min, max;
	Tmpl8::vec2* pos;
	Type type;
	//collider that had a collision with this one.
	Collider* collision;
	//collision flag
	bool toDeactivate = false;
	/**
	 * \brief Offsets the collider with the offset vector.
	 * \param offset A vector that will act the temporary position.
	 * \return returns a copy of the collider at the specified offset.
	 */
	Collider At(const Tmpl8::vec2& offset) const;
	/**
	 * \brief Checks if the collider is colliding with this instance.
	 * \param collider The collider to be checked if collides with this instance.
	 * \return Whether a collision is present.
	 */
	bool Collides(const Collider& collider) const;
	/**
	 * \brief Checks if the 2 colliders are colliding.
	 * \param a The first collider.
	 * \param b The second collider.
	 * \return Whether a collision is present.
	 */
	static bool Collides(const Collider& a, const Collider& b);
	/**
	 * \brief Checks collision on the y axis for the two colliders.
	* \param a The first collider.
	 * \param b The second collider.
	 * \return Whether a collision is present on the y axis.
	 */
	static bool CollidesY(const Collider& a, const Collider& b);
	/**
	 * \brief Checks collision on the x axis for the two colliders.
	* \param a The first collider.
	 * \param b The second collider.
	 * \return Whether a collision is present on the x axis.
	 */
	static bool CollidesX(const Collider& a, const Collider& b);
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

	/**
	 * \brief Checks if the collider is in the viewable screen at the position.
	 * \param _offset Vector to offset the collider.
	 * \param collider The collider that needs to be checked.
	 * \return Whether the object is in game screen.
	 */
	static bool InGameScreen(const Tmpl8::vec2& _offset, const Collider& collider);
	/**
	 * \brief Checks if the position is in the viewable screen.
	 * \param position Vector that needs to be checked.
	 * \return Whether the object is in game screen.
	 */
	static bool InGameScreen(const Tmpl8::vec2& position);
	/**
	 * \brief Checks if the collider is in the playable area.
	 * \param collider Collider that needs to be checked.
	 * \return Whether the object is in playable area.
	 */
	static bool InGameBounds(const Collider& collider);
	/**
	 * \brief Checks if the collider is in the playable area.
	 * \param _offset Vector that will act as an offset for the collider.
	 * \param collider Collider that needs to be checked.
	 * \return Whether the object is in playable area.
	 */
	static bool InGameBounds(const Tmpl8::vec2& _offset, const Collider& collider);

	/**
	 * \brief Returns the normal vector for the edges of the screen.
	 * \param _offset Vector that will act as an offset for the collider.
	 * \param collider Collider of the object that needs to be checked.
	 * \return The normal of the screen that is intersecting with the object.
	 */
	static Tmpl8::vec2 GetNormalEdgeScreen(const Tmpl8::vec2& _offset, const Collider& collider);

};


