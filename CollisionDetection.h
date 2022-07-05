#pragma once
#include "vector.h"
#include "MergeSort.h"
#include "Projectile.h"
class CollisionDetection :public Updateable, public Callable
{
public:
	CollisionDetection(int maxX, vector<Projectile*>& collidables);
	~CollisionDetection();
	void ConvertToFloat();
	void SortOnX();
	virtual void Update(float deltaTime) override;
	// Inherited via Callable
	virtual void Call() override;
private:
	vector<Projectile*>* axisToSort;
	vector<float> axisSorted;
	MergeSort<float> mergeSort;
	Timer* timer;
	int maxX;





};

