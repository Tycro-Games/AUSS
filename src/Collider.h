#pragma once
#include "template.h"

struct Collider
{
	enum class Type
	{
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
	/// <summary>
	/// The two vectors that make up the square as a collider.
	/// </summary>
	Tmpl8::vec2 min, max;
	/**
	 * \brief Pointer to the position of the object, could be null.
	 */
	Tmpl8::vec2* pos;
	/**
	 * \brief The type of object that this collider represents.
	 */
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
};
