#pragma once
//based on this tutorial https://www.youtube.com/watch?v=eED4bSkYCB8, sweep and prune
#include "Projectile.h"

#include <algorithm>
#include <vector>
class CollisionDetection :public Updateable, public Callable
{
public:

	CollisionDetection();

	~CollisionDetection();
	void DetectCollisions();

	void CheckProjectile(std::vector<Collider*>& allPairs, int i, int j);

	virtual void Update(float deltaTime) override;
	// Inherited via Callable
	virtual void Call() override;
private:

	Timer timer;

};

