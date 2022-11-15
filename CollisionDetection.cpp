#include "CollisionDetection.h"
#include "game.h"
using namespace std;
using namespace Tmpl8;
CollisionDetection::CollisionDetection()
{
	timer = new Timer(this, .05f, true);
}



CollisionDetection::~CollisionDetection()
{
	delete timer;
}

//this is what the lambda function does below
//bool CompareXPositions(Collider* a, Collider* b) {
//	return a->pos->x < b->pos->x;
//}
void CollisionDetection::DetectCollisions()
{

	vector <Collider*> allPairs;
	vector <Collider*> activeIntervals;
	//add enemies and projectiles

	//sort on x axis
	if (Game::Get().colliders.size() == 0)
		return;
	sort(Game::Get().colliders.begin(), Game::Get().colliders.end(), [](const Collider* a, const Collider* b) { return a->pos->x < b->pos->x; });

	for (int i = 0; i < Game::Get().Tmpl8::Game::colliders.size(); i++)
	{
		Collider* a = Game::Get().colliders[i];

		for (int j = 0; j < activeIntervals.size(); j++) {
			//possible collision
			Collider* b = activeIntervals[j];

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

				activeIntervals.erase(activeIntervals.begin() + j);

				j--;
			}
		}
		activeIntervals.push_back(a);
	}

	for (int i = 0; i < allPairs.size(); i += 2) {
		//trigger the collision flags for the colliders
		CheckProjectile(allPairs, i, i + 1);


	}

}

void CollisionDetection::CheckProjectile(vector<Collider*>& allPairs, int i, int j)
{
	if (allPairs[i]->type == Collider::Projectile) {
		allPairs[i]->toDeactivate = true;
		allPairs[i]->collision = allPairs[i + 1];
	}
	if (allPairs[j]->type == Collider::Projectile) {
		allPairs[j]->toDeactivate = true;
		allPairs[j]->collision = allPairs[i];
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

