#pragma once
#include "vector.h"
#include "Projectile.h"
class CollisionDetection
{
public:
	CollisionDetection(int maxX);
	~CollisionDetection();
	static void SortOnX(vector<Projectile*>& collidables);
private:

	int maxX;
};

