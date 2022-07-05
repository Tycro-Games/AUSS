#include "CollisionDetection.h"

CollisionDetection::CollisionDetection(int maxX, vector<Projectile*>& collidables) :
	maxX(maxX),
	axisToSort(&collidables),
	axisSorted(),
	mergeSort(&axisSorted),
	timer(new Timer(this, 2.0f, true))
{
	ConvertToFloat();
}

CollisionDetection::~CollisionDetection()
{
	delete timer;
}

void CollisionDetection::ConvertToFloat()
{
	axisSorted.removeAll();

	for (int i = 0; i < axisToSort->getCount(); i++)
		axisSorted.push_back(axisToSort->get(i)->pos->x);
}

void CollisionDetection::SortOnX()
{
	if (axisSorted.getCount() == 0)
		return;
	else {
		mergeSort.Sort(0, axisSorted.getCount() - 1);
		axisSorted.print();
	}


}

void CollisionDetection::Update(float deltaTime)
{
	timer->Update(deltaTime);
}


void CollisionDetection::Call()
{
	ConvertToFloat();
	SortOnX();
}

