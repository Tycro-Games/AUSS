#pragma once
#include "vector.h"
#include "MergeSort.h"
#include "Projectile.h"
class CollisionDetection :public Updateable, public Callable
{
public:
	CollisionDetection(int maxX, vector<Projectile*>& collidables);
	~CollisionDetection();
	void DetectCollisions();


	virtual void Update(float deltaTime) override;
	// Inherited via Callable
	virtual void Call() override;
private:
	vector<Projectile*>* axisToSort;
	MergeSort<Projectile*> mergeSort;
	Timer* timer;
	int maxX;





};

