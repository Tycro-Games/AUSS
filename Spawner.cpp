#include "Spawner.h"


Spawner::Spawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Tmpl8::Sprite* explosion) :
	pos(pos),
	dir(dir),
	explosionSprite(explosion)
{
}

Spawner::~Spawner()
{
	for (int i = 0; i < updateObjects.getCount() - 1; i++) {
		updateObjects[i]->sprite = nullptr;//the sprite is only a pointer that is cleaned up by sub spawners
		delete updateObjects[i];
	}
	updateObjects.removeAll();
	delete explosionSprite;
}
Tmpl8::vec2 Spawner::GetDirDeviation()
{
	//random direction
	//static cast is safe
	float x = randomNumbers.RandomBetweenFloats(MIN_DEVIATION, MAX_DEVIATION);
	float y = randomNumbers.RandomBetweenFloats(MIN_DEVIATION, MAX_DEVIATION);
	//adding multiplier
	x *= deviationMultiplier;
	y *= deviationMultiplier;
	return Tmpl8::vec2(x, y);
}


void Spawner::AddExplosionToPool(ExplosionBullet* entity)
{
	entity->SetActive(false);

	poolOfExplosions.AddElement(entity);
}

void Spawner::CreateMoreExplosions()
{
	ExplosionBullet* bullet = new ExplosionBullet(explosionSprite, this);
	updateObjects.push_back(bullet);

	AddExplosionToPool(bullet);
}

void Spawner::SpawnExplosions(Tmpl8::vec2 pos)
{
	if (poolOfExplosions.getCount() == 0)
		CreateMoreExplosions();
	ExplosionBullet* bullet = poolOfExplosions.PopElement();

	bullet->Init(pos);
}


