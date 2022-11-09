#include "CollisionDetection.h"
#include "game.h"

CollisionDetection::CollisionDetection()
{
	timer = new Timer(this, .05f, true);
}



CollisionDetection::~CollisionDetection()
{
	delete timer;
}



void CollisionDetection::DetectCollisions()
{

	dynamic_array <Collider*> allPairs;
	dynamic_array <Collider*> activeIntervals;
	//add enemies and projectiles

	//sort on x axis
	if (Tmpl8::Game::cols.getCount() == 0)
		return;
	mergeSort.Init(&Tmpl8::Game::cols);
	mergeSort.Sort(0, Tmpl8::Game::cols.getCount() - 1);

	for (int i = 0; i < Tmpl8::Game::cols.getCount(); i++)
	{
		Collider* a = Tmpl8::Game::cols.get(i);

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

	for (int i = 0; i < allPairs.getCount(); i += 2) {
		//trigger the collision flags for the colliders
		allPairs[i]->toDeactivate = true;
		allPairs[i]->collision = allPairs[i + 1];
		allPairs[i + 1]->toDeactivate = true;
		allPairs[i + 1]->collision = allPairs[i];

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

