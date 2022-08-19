#pragma once
#include "vector.h"
#include "MergeSort.h"
#include "Projectile.h"

class CollisionDetection :public Updateable, public Callable
{
public:
	CollisionDetection(int maxX, vector<Collider*>& collidables);
	~CollisionDetection();
	void DetectCollisions();


	virtual void Update(float deltaTime) override;
	// Inherited via Callable
	virtual void Call() override;
private:
	vector<Collider*>* axisToSort;
	MergeSort<Collider*> mergeSort;
	Timer* timer;
	int maxX;





};

