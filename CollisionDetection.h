#pragma once
//based on this tutorial https://www.youtube.com/watch?v=eED4bSkYCB8 and https://github.com/YulyaLesheva/Sweep-And-Prune-algorithm, sweep and prune
#include "Projectile.h"

#include <algorithm>
#include <vector>
class CollisionDetection :public Updateable
{
public:

	CollisionDetection();

	~CollisionDetection() = default;
	void DetectCollisions();

	void CheckPair(const std::vector<Collider*>& allPairs, size_t i, size_t j);

	void Update(float deltaTime) override;
private:

	Timer timer;

};

