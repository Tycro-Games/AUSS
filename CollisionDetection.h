#pragma once

#include "MergeSort.h"
#include "Projectile.h"

class CollisionDetection :public Updateable, public Callable
{
public:

	CollisionDetection();

	~CollisionDetection();
	void DetectCollisions();

	virtual void Update(float deltaTime) override;
	// Inherited via Callable
	virtual void Call() override;
private:

	MergeSort<Collider*> mergeSort;
	Timer* timer;

};

