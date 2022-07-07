#include "CollisionDetection.h"

CollisionDetection::CollisionDetection(int maxX, vector<Projectile*>& collidables) :
	maxX(maxX),
	axisToSort(&collidables),
	mergeSort(axisToSort),
	timer(new Timer(this, .08f, true))
{
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
		vector <Projectile*> allPairs;
		vector <Projectile*> activeIntervals;
		//sort on x axis
		mergeSort.Sort(0, axisToSort->getCount() - 1);

		for (int i = 0; i < axisToSort->getCount(); i++)
		{
			Projectile* a = axisToSort->get(i);

			for (int j = 0; j < activeIntervals.getCount(); j++) {
				//possible collision
				Projectile* b = activeIntervals.get(j);

				if (Collider::CollidesX(a->getColl()->At(*a->pos),
					b->getColl()->At(*b->pos)))
				{
					//check intersection
					if (Collider::CollidesY(a->getColl()->At(*a->pos),
						b->getColl()->At(*b->pos))) {
						allPairs.push_back(a);
						allPairs.push_back(b);
					}
				}
				else {
					activeIntervals.removeAtIndex(j);
					j--;
				}
			}
			activeIntervals.push_back(a);



		}
		for (int i = 0; i < allPairs.getCount(); i++) {
			allPairs[i]->ResetBullet();
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

