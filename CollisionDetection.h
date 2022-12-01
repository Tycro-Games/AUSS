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

	void CheckProjectile(std::vector<Collider*>& allPairs, int i, int j);

	void Update(float deltaTime) override;
private:

	Timer timer;

};

