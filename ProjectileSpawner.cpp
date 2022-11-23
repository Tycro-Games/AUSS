#include "ProjectileSpawner.h"

#include <string>
#include <iostream>

#include "game.h"
using namespace Tmpl8;
using namespace std;
ProjectileSpawner::ProjectileSpawner(const Tmpl8::vec2 offset, const filesystem::path& _projectileSprite, const  filesystem::path& _explosionSprite)
	:
	Spawner(_explosionSprite),
	projectileSprite(new Surface(_projectileSprite.string().c_str()), 16),
	offset(offset)


{
	desiredTime = 0;
	currentTime = 0;
}

void ProjectileSpawner::Init()
{
	for (size_t i = 0; i < updateObjects.size(); i++)
		if (updateObjects[i]->getUpdateable())
			delete updateObjects[i];
	updateObjects.clear();

	for (size_t i = 0; i < poolOfProjectiles.size(); i++) {
		delete poolOfProjectiles[i];
	}
	poolOfProjectiles.clear();

	Spawner::ResetExplosions();
	for (int i = 0; i < MAX_PROJECTILES; i++) {
		CreateMoreProjectiles();
	}
	for (int i = 0; i < MAX_EXPLOSIONS; i++) {
		CreateMoreExplosions();
	}




	fireRate = FIRE_RATE;
	desiredTime = 0;
	currentTime = 0;
	waveProjectiles = 0;
	totalProjectiles = 0;
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
	Game::Get().RemoveMoveable(entity->getMoveable());
	Game::Get().RemoveCollider(entity->getColl());

	entity->SetActive(false);
	poolOfProjectiles.push_back(entity);

}


ProjectileSpawner::~ProjectileSpawner()
{

}

void ProjectileSpawner::CreateMoreProjectiles()
{
	Projectile* entity = new Projectile(PosDir(), &projectileSprite, this);
	updateObjects.push_back(entity);

	AddProjectileToPool(entity);

}


void ProjectileSpawner::SpawnProjectiles()
{
	if (poolOfProjectiles.size() == 0)
		CreateMoreProjectiles();

	Projectile* projectile = poolOfProjectiles[poolOfProjectiles.size() - 1];
	poolOfProjectiles.pop_back();

	vec2 randomDir = GetDirDeviation();
	vec2 playerPos = Game::Get().getPlayer().pos;
	vec2 playerDir = Game::Get().getPlayer().GetDir();
	vec2 randomizedDir = (playerDir + randomDir).normalized();
	projectile->Init(PosDir{ playerPos + randomizedDir * OFFSET_MULTIPLIER,randomizedDir });
	AddProjectilesCount();
	Game::Get().AddCollider(projectile->getColl());
	Game::Get().AddMoveable(projectile->getMoveable());
}

void ProjectileSpawner::AddProjectilesCount()
{
	waveProjectiles++;
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

	for (int i = 0; i < updateObjects.size(); i++)
		updateObjects[i]->Update(deltaTime);

}

void ProjectileSpawner::Render(Tmpl8::Surface* screen)
{
	auto inactive = std::string("Bullets left:" + std::to_string(poolOfProjectiles.size()));

	screen->Print(inactive.c_str(), 10, 10, 0x00FF0000);

	auto inactiveB = std::string("Explosions left:" + std::to_string(poolOfExplosions.size()));

	screen->Print(inactiveB.c_str(), 10, 20, 0x00FF0000);

	auto total = std::string("Objects active:" + std::to_string(updateObjects.size() - poolOfProjectiles.size() - poolOfExplosions.size()));

	screen->Print(total.c_str(), 10, 30, 0x00FF0000);
	auto firerate = std::string("Firerate: " + std::to_string(fireRate));

	screen->Print(firerate.c_str(), 10, 60, 0x00FF0000);

	screen->Print("Use up arrow and down arrow to adjust the firerate", 10, 70, 0x00FF0000);
	screen->Print("Use space bar to dash", 10, 80, 0x00FF0000);
	for (int i = 0; i < updateObjects.size(); i++)
		updateObjects[i]->Render(screen);

}

unsigned int ProjectileSpawner::getWaveProjectiles() const
{
	return waveProjectiles;
}

unsigned int ProjectileSpawner::getTotalProjectiles() const
{
	return totalProjectiles;
}

void ProjectileSpawner::ResetWaveProjectiles()
{
	totalProjectiles += waveProjectiles;
	waveProjectiles = 0;
}



