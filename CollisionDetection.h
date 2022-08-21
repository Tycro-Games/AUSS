#pragma once
#include "MergeSort.h"
#include "Projectile.h"

class CollisionDetection :public Updateable, public Callable
{
public:

	CollisionDetection(vector<Collider*>&, vector<Collider*>&);

	~CollisionDetection();
	void DetectCollisions();



	virtual void Update(float deltaTime) override;
	// Inherited via Callable
	virtual void Call() override;
private:
	vector<Collider*>* Projectiles;
	vector<Collider*>* Enemies;

	MergeSort<Collider*> mergeSort;
	Timer* timer;





};

