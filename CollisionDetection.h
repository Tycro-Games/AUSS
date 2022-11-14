#pragma once
//based on this tutorial https://www.youtube.com/watch?v=eED4bSkYCB8, sweep and prune
#include "MergeSort.h"
#include "Projectile.h"

class CollisionDetection :public Updateable, public Callable
{
public:

	CollisionDetection();

	~CollisionDetection();
	void DetectCollisions();

	void CheckProjectile(dynamic_array<Collider*>& allPairs, int i, int j);

	virtual void Update(float deltaTime) override;
	// Inherited via Callable
	virtual void Call() override;
private:

	MergeSort<Collider*> mergeSort;
	Timer* timer;

};

