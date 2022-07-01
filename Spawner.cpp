#include "Spawner.h"


#include <string>
#include <iostream>
vector <Projectile*> Spawner::poolOfProjectiles;
vector <ExplosionBullet*> Spawner::poolOfExplosions;
bool Spawner::isInit;
Spawner::Spawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Tmpl8::Sprite* tospawn, Tmpl8::Sprite* explosion, float FireRate)
	:pos(pos),
	dir(dir),
	toSpawn(tospawn),
	explosionSprite(explosion)
{

	isInit = false;
	for (int i = 0; i < MAX_PROJECTILES; i++) {
		CreateMoreProjectiles();

	}


	isInit = true;
	fireRate = FireRate;
	desiredTime = 0;
	currentTime = 0;
}

void Spawner::AddProjectileToPool(Projectile* entity)
{
	entity->SetActive(false);

	poolOfProjectiles.push_back(entity);
	if (isInit)
		SpawnExplosions(*entity->pos);

}
void Spawner::AddExplosionToPool(ExplosionBullet* entity)
{
	entity->SetActive(false);

	poolOfExplosions.push_back(entity);
}

Spawner::~Spawner()
{
	poolOfProjectiles.removeAll();
	poolOfExplosions.removeAll();
	updateObjects.removeAll();
	delete pos;
	delete dir;

}

void Spawner::CreateMoreProjectiles()
{
	Projectile* entity = new Projectile(PosDir(*pos + *dir * OFFSET, *dir), toSpawn, explosionSprite);
	updateObjects.push_back(entity);

	AddProjectileToPool(entity);
	if (poolOfProjectiles.getCount() > poolOfExplosions.getCount())
		CreateMoreExplosions();
}
void Spawner::CreateMoreExplosions()
{
	ExplosionBullet* bullet = new ExplosionBullet(explosionSprite);
	updateObjects.push_back(bullet);

	AddExplosionToPool(bullet);
}



void Spawner::SpawnProjectiles()
{
	if (poolOfProjectiles.getCount() == 0)
		CreateMoreProjectiles();

	Projectile* projectile = poolOfProjectiles.get(poolOfProjectiles.getCount() - 1);
	projectile->SetActive(true);
	projectile->Init(PosDir{ (*pos) + (*dir), *dir });

	poolOfProjectiles.pop_back();
}
void Spawner::SpawnExplosions(Tmpl8::vec2 pos)
{

	ExplosionBullet* bullet = poolOfExplosions.get(poolOfExplosions.getCount() - 1);
	bullet->SetActive(true);
	bullet->Init(pos);

	poolOfExplosions.pop_back();
}


void Spawner::setFlag(bool fire)
{
	isSpawning = fire;
}




void Spawner::Update(float deltaTime)
{
	for (int i = 0; i < updateObjects.getCount(); i++)
		updateObjects.get(i)->Update(deltaTime);

	if (currentTime >= desiredTime) {
		if (isSpawning) {
			SpawnProjectiles();
			desiredTime = currentTime + fireRate;
		}
	}
	else
		currentTime += deltaTime;
}

void Spawner::Render(Tmpl8::Surface* screen)
{
	auto inactive = std::string("Bullets left:" + std::to_string(poolOfProjectiles.getCount()));

	screen->Print(inactive.c_str(), 10, 10, 0xffffffff);


	auto inactiveB = std::string("Explosions left:" + std::to_string(poolOfExplosions.getCount()));

	screen->Print(inactiveB.c_str(), 10, 20, 0xffffffff);

	auto total = std::string("Objects active:" + std::to_string(updateObjects.getCount() - poolOfProjectiles.getCount() - poolOfExplosions.getCount()));

	screen->Print(total.c_str(), 10, 30, 0xffffffff);
	for (int i = 0; i < updateObjects.getCount(); i++)
		updateObjects.get(i)->Render(screen);

}

