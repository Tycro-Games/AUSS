#include "CollisionDetection.h"

CollisionDetection::CollisionDetection(int maxX, vector<Collider*>& collidables) :
	maxX(maxX),
	axisToSort(&collidables),
	mergeSort(axisToSort)

{
	timer = new Timer(this, .05f, true);
}

CollisionDetection::~CollisionDetection()
{
	delete timer;
}



void CollisionDetection::DetectCollisions()
{

	if (axisToSort->getCount() == 0)
		return;
	else {
		vector <Collider*> allPairs;
		vector <Collider*> activeIntervals;
		//sort on x axis
		mergeSort.Sort(0, axisToSort->getCount() - 1);

		for (int i = 0; i < axisToSort->getCount(); i++)
		{
			Collider* a = axisToSort->get(i);

			for (int j = 0; j < activeIntervals.getCount(); j++) {
				//possible collision
				Collider* b = activeIntervals.get(j);

				if (Collider::CollidesX(a->At(*a->pos),
					b->At(*b->pos)))
				{
					//check if there is a collision
					if (Collider::CollidesY(a->At(*a->pos),
						b->At(*b->pos))) {
						allPairs.push_back(a);
						allPairs.push_back(b);
					}
				}
				else {
					//update the interval if no collision

					activeIntervals.removeAtIndex(j);

					j--;
				}
			}
			activeIntervals.push_back(a);
		}
		for (int i = 0; i < allPairs.getCount(); i++) {
			allPairs[i]->toDeactivate = true;

		}
	}
}




void CollisionDetection::Update(float deltaTime)
{
	timer->Update(deltaTime);
}


void CollisionDetection::Call()
{
	DetectCollisions();
}

