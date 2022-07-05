#include "CollisionDetection.h"

CollisionDetection::CollisionDetection(int maxX, vector<Projectile*>& collidables) :
	maxX(maxX),
	axisToSort(&collidables),
	mergeSort(axisToSort),
	timer(new Timer(this, 2.0f, true))
{
}

CollisionDetection::~CollisionDetection()
{
	delete timer;
}



void CollisionDetection::SortOnX()
{
	if (axisToSort->getCount() == 0)
		return;
	else {
		mergeSort.Sort(0, axisToSort->getCount() - 1);
		axisToSort->print();
	}


}

void CollisionDetection::Update(float deltaTime)
{
	timer->Update(deltaTime);
}


void CollisionDetection::Call()
{
	SortOnX();
}

