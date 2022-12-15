#include "ProjectileSpawner.h"

#include <string>

#include "game.h"
using namespace Tmpl8;
using namespace std;
ProjectileSpawner::ProjectileSpawner(const Tmpl8::vec2 offset, const filesystem::path& _projectileSprite, const  filesystem::path& _explosionSprite)
	:
	Spawner(_explosionSprite),
	offset(offset),
	projectileSprite(new Surface(_projectileSprite.string().c_str()), 16)


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

void ProjectileSpawner::AddProjectileToPool(Projectile* entity)
{
	Game::Get().RemoveMoveable(entity->getMoveable());
	Game::Get().RemoveCollider(entity->getColl());

	entity->SetActive(false);
	poolOfProjectiles.push_back(entity);

}




void ProjectileSpawner::CreateMoreProjectiles()
{
	Projectile* entity = new Projectile(PosDir(), &projectileSprite, this);
	updateObjects.push_back(entity);

	AddProjectileToPool(entity);

}


void ProjectileSpawner::SpawnProjectiles()
{
	if (poolOfProjectiles.empty())
		CreateMoreProjectiles();

	Projectile* projectile = poolOfProjectiles[poolOfProjectiles.size() - 1];
	poolOfProjectiles.pop_back();

	const vec2 randomDir = MathFunctions::GetRandomVec2(MIN_DEVIATION, MAX_DEVIATION);
	const vec2 playerPos = Game::Get().getPlayer().pos;
	const vec2 playerDir = Game::Get().getPlayer().GetDir();
	const vec2 randomizedDir = (playerDir + randomDir).normalized();
	projectile->Init(PosDir{ playerPos + randomizedDir * OFFSET_MULTIPLIER,randomizedDir });
	waveProjectiles++;
	Game::Get().AddCollider(projectile->getColl());
	Game::Get().AddMoveable(projectile->getMoveable());
}


void ProjectileSpawner::setFlag(const bool fire)
{
	isSpawning = fire;
}

void ProjectileSpawner::Update(const float deltaTime)
{

	if (currentTime >= desiredTime) {
		if (isSpawning) {
			Game::Get().PlaySound(SoundID::playerShooting);
			SpawnProjectiles();
			desiredTime = currentTime + fireRate;
		}
	}
	else
		currentTime += deltaTime;

	for (size_t i = 0; i < updateObjects.size(); i++)
		updateObjects[i]->Update(deltaTime);

}

void ProjectileSpawner::Render(Tmpl8::Surface* screen)
{
	const auto firerate = std::string("Firerate: " + std::to_string(fireRate));



	for (size_t i = 0; i < updateObjects.size(); i++)
		updateObjects[i]->Render(screen);
#ifdef _DEBUG
	const auto inactive = std::string("Bullets left:" + std::to_string(poolOfProjectiles.size()));

	screen->Print(inactive.c_str(), 10, 10, 0x00FF0000);

	const auto inactiveB = std::string("Explosions left:" + std::to_string(poolOfExplosions.size()));

	screen->Print(inactiveB.c_str(), 10, 20, 0x00FF0000);

	const auto total = std::string("Objects active:" + std::to_string(updateObjects.size() - poolOfProjectiles.size() - poolOfExplosions.size()));

	screen->Print(total.c_str(), 10, 30, 0x00FF0000);
#endif
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



