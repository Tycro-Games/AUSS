#include "Spawner.h"


Spawner::Spawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Tmpl8::Sprite* explosion) :
	pos(pos),
	dir(dir),
	explosionSprite(explosion)
{
}

Spawner::~Spawner()
{

}

vector<Collider*>& Spawner::GetActiveColliders()
{
	return activeColliders;
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


