#pragma once
//based on this tutorial https://www.youtube.com/watch?v=eED4bSkYCB8 and https://github.com/YulyaLesheva/Sweep-And-Prune-algorithm, sweep and prune
#include "Projectile.h"

#include <vector>

class CollisionDetection : public Updateable
{
public:
	CollisionDetection();

	~CollisionDetection() override = default;
	void DetectCollisions();


	void Update(float deltaTime) override;

private:
	void CheckPair(const std::vector<Collider*>& allPairs, size_t i, size_t j);
	Timer timer;
};
