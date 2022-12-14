// ReSharper disable CppClangTidyModernizeLoopConvert
// ReSharper disable CppTooWideScopeInitStatement
#include "CollisionDetection.h"
#include "game.h"
using namespace std;
using namespace Tmpl8;

CollisionDetection::CollisionDetection()
{
	timer.Init(bind(&CollisionDetection::DetectCollisions, this), .05f, true);
}


//this is what the lambda function does below
//bool CompareXPositions(Collider* a, Collider* b) {
//	return a->pos->x < b->pos->x;
//}
void CollisionDetection::DetectCollisions()
{
	vector<Collider*> allPairs;
	vector<Collider*> activeIntervals;
	//add enemies and projectiles

	//sort on x axis
	if (Game::Get().getColliders().empty())
		return;
	sort(Game::Get().getColliders().begin(), Game::Get().getColliders().end(), [](const Collider* a, const Collider* b)
		{
			return a->pos->x < b->pos->x;
		});

	for (size_t i = 0; i < Game::Get().getColliders().size(); i++)
	{
		Collider* a = Game::Get().getColliders()[i];

		for (size_t j = 0; j < activeIntervals.size(); j++)
		{
			//possible collision
			Collider* b = activeIntervals[j];

			if (Collider::CollidesX(a->At(*a->pos),
				b->At(*b->pos)))
			{
				//check if there is a collision
				if (Collider::CollidesY(a->At(*a->pos),
					b->At(*b->pos)))
				{
					allPairs.push_back(a);
					allPairs.push_back(b);
				}
			}
			else
			{
				//update the interval if no collision
				activeIntervals.erase(activeIntervals.begin() + j);

				j--;
			}
		}
		activeIntervals.push_back(a);
	}

	for (size_t i = 0; i < allPairs.size(); i += 2)
	{
		//trigger the collision flags for the getColliders()
		CheckPair(allPairs, i, i + 1);
	}
}

void CollisionDetection::CheckPair(const vector<Collider*>& allPairs, const size_t i, const size_t j)
{
	if (allPairs[i]->type == Collider::Type::projectile)
	{
		allPairs[i]->toDeactivate = true;
		allPairs[i]->collision = allPairs[j];
	}
	if (allPairs[j]->type == Collider::Type::projectile)
	{
		allPairs[j]->toDeactivate = true;
		allPairs[j]->collision = allPairs[i];
	}
}

void CollisionDetection::Update(const float deltaTime)
{
	timer.Update(deltaTime);
}
