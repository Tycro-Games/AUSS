#pragma once
//based on this tutorial https://www.youtube.com/watch?v=eED4bSkYCB8 and https://github.com/YulyaLesheva/Sweep-And-Prune-algorithm, sweep and prune
#include "Projectile.h"


constexpr float TIME_BETWEEN_DETECTIONS = 0.05f;

class CollisionDetection final : public Updateable
{
public:
	CollisionDetection();

	~CollisionDetection() override = default;
	/**
	 * \brief Checks whether pairs of objects are colliding.
	 */
	void DetectCollisions();

	void Update(float deltaTime) override;

private:
	/**
	 * \brief Flags the colliders that there had been a collision.
	 * \param a The first collider to be flagged.
	 * \param b The second collider to be flagged.
	 */
	void FlagPair(Collider* a, Collider* b);
	Timer timeBetweenDetections;
};
