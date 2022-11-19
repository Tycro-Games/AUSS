#include "Spawner.h"

using namespace Tmpl8;

Spawner::Spawner(const std::filesystem::path& explosion, unsigned int numberOfFrames) :
	explosionSprite(new Surface(explosion.string().c_str()), numberOfFrames)
{
}

Spawner::Spawner(const Tmpl8::Sprite& explosion) :
	explosionSprite(explosion)
{
}




Spawner::~Spawner()
{
	if (updateObjects.size() > 0)
		for (size_t i = 0; i < updateObjects.size() - 1; i++) {
			delete updateObjects[i];
		}
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
	ExplosionBullet* bullet = new ExplosionBullet(&explosionSprite, this, Tmpl8::vec2(0));
	updateObjects.push_back(bullet);

	AddExplosionToPool(bullet);
}

void Spawner::SpawnExplosions(Tmpl8::vec2 p)
{
	if (poolOfExplosions.getCount() == 0)
		CreateMoreExplosions();
	ExplosionBullet* bullet = poolOfExplosions.PopElement();

	bullet->Init(p);
}


