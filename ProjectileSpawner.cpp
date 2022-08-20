#include "ProjectileSpawner.h"

#include <string>
#include <iostream>

ProjectileSpawner::ProjectileSpawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Tmpl8::Sprite* tospawn, Tmpl8::Sprite* explosion)
	:Spawner(pos, dir),
	projectileSprite(tospawn),
	explosionSprite(explosion),
	activeProjectiles(),
	colDec(activeProjectiles)
{

	for (int i = 0; i < MAX_PROJECTILES; i++) {
		CreateMoreProjectiles();
	}
	for (int i = 0; i < MAX_EXPLOSIONS; i++) {
		CreateMoreExplosions();
	}


	fireRate = FIRE_RATE;
	desiredTime = 0;
	currentTime = 0;
}

void ProjectileSpawner::ChangeFireSpeed(float speed) {

	fireRate += speed;
	if (fireRate < MIN_RATE)
		fireRate = MIN_RATE;
	if (fireRate > MAX_RATE)
		fireRate = MAX_RATE;
}
void ProjectileSpawner::AddProjectileToPool(Projectile* entity)
{
	entity->SetActive(false);
	activeProjectiles.remove(entity->getColl());
	poolOfProjectiles.AddElement(entity);

}
void ProjectileSpawner::AddExplosionToPool(ExplosionBullet* entity)
{
	entity->SetActive(false);

	poolOfExplosions.AddElement(entity);
}

ProjectileSpawner::~ProjectileSpawner()
{


}

void ProjectileSpawner::CreateMoreProjectiles()
{
	Projectile* entity = new Projectile(PosDir(*pos + *dir * OFFSET, *dir), projectileSprite, this);
	updateObjects.push_back(entity);

	AddProjectileToPool(entity);

}
void ProjectileSpawner::CreateMoreExplosions()
{
	ExplosionBullet* bullet = new ExplosionBullet(explosionSprite, this);
	updateObjects.push_back(bullet);

	AddExplosionToPool(bullet);
}

void ProjectileSpawner::SpawnProjectiles()
{
	if (poolOfProjectiles.getCount() == 0)
		CreateMoreProjectiles();

	Projectile* projectile = poolOfProjectiles.PopElement();

	Tmpl8::vec2 randomDir = GetDirDeviation();
	projectile->Init(PosDir{ (*pos) + (*dir), (*dir + randomDir).normalized() });
	activeProjectiles.push_back(projectile->getColl());
}

Tmpl8::vec2 ProjectileSpawner::GetDirDeviation()
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

void ProjectileSpawner::SpawnExplosions(Tmpl8::vec2 pos)
{
	if (poolOfExplosions.getCount() == 0)
		CreateMoreExplosions();
	ExplosionBullet* bullet = poolOfExplosions.PopElement();

	bullet->Init(pos);

}

void ProjectileSpawner::setFlag(bool fire)
{
	isSpawning = fire;
}

void ProjectileSpawner::Update(float deltaTime)
{

	if (currentTime >= desiredTime) {
		if (isSpawning) {
			SpawnProjectiles();
			desiredTime = currentTime + fireRate;
		}
	}
	else
		currentTime += deltaTime;
	colDec.Update(deltaTime);
	for (int i = 0; i < updateObjects.getCount(); i++)
		updateObjects[i]->Update(deltaTime);

}

void ProjectileSpawner::Render(Tmpl8::Surface* screen)
{
	auto inactive = std::string("Bullets left:" + std::to_string(poolOfProjectiles.getCount()));

	screen->Print(inactive.c_str(), 10, 10, 0xffffffff);

	auto inactiveB = std::string("Explosions left:" + std::to_string(poolOfExplosions.getCount()));

	screen->Print(inactiveB.c_str(), 10, 20, 0xffffffff);

	auto total = std::string("Objects active:" + std::to_string(updateObjects.getCount() - poolOfProjectiles.getCount() - poolOfExplosions.getCount()));

	screen->Print(total.c_str(), 10, 30, 0xffffffff);
	auto firerate = std::string("Firerate: " + std::to_string(fireRate));

	screen->Print(firerate.c_str(), 10, 60, 0xffffffff);

	screen->Print("Use up arrow and down arrow to adjust the firerate", 10, 70, 0xffffffff);
	screen->Print("Use space bar to dash", 10, 80, 0xffffffff);
	for (int i = 0; i < updateObjects.getCount(); i++)
		updateObjects[i]->Render(screen);

}