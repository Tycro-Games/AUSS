#include "Spawner.h"

using namespace Tmpl8;

Spawner::Spawner(const std::filesystem::path& explosion, const unsigned int numberOfFrames) :
	explosionSprite(new Sprite(new Surface(explosion.string().c_str()), numberOfFrames))
{
}

Spawner::Spawner(Sprite* explosion) :
	explosionSprite(explosion)
{
}




Spawner::~Spawner()
{
	if (!updateObjects.empty())
		for (size_t i = 0; i < updateObjects.size() - 1; i++) {
			updateObjects[i]->sprite = nullptr;//shares this with others
			delete updateObjects[i];
		}
	updateObjects.clear();
}


void Spawner::ResetExplosions()
{
	for (int i = 0; i < poolOfExplosions.size(); i++)
		delete poolOfExplosions[i];
	poolOfExplosions.clear();
}


void Spawner::AddExplosionToPool(ExplosionBullet* entity)
{
	entity->SetActive(false);

	poolOfExplosions.push_back(entity);
}

void Spawner::CreateMoreExplosions()
{
	ExplosionBullet* bullet = new ExplosionBullet(explosionSprite, this, vec2(0));
	updateObjects.push_back(bullet);

	AddExplosionToPool(bullet);
}

void Spawner::SpawnExplosions(const vec2 p)
{
	if (poolOfExplosions.size() == 0)
		CreateMoreExplosions();
	ExplosionBullet* bullet = poolOfExplosions[poolOfExplosions.size() - 1];
	poolOfExplosions.pop_back();

	bullet->Init(p);
}


