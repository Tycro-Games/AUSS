#include "CollisionDetection.h"


CollisionDetection::CollisionDetection(int maxX) :
	maxX(maxX)
{
}

CollisionDetection::~CollisionDetection()
{
}

void CollisionDetection::SortOnX(vector<Projectile*>& collidables)
{
	if (collidables.getCount() == 0)
		return;


}
