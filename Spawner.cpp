#include "Spawner.h"

#include <string>
#include <iostream>
vector <Projectile*> Spawner::poolOfProjectiles;
Spawner::Spawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Tmpl8::Sprite* tospawn, Tmpl8::Sprite* explosion, float FireRate)
	:pos(pos),
	dir(dir),
	toSpawn(tospawn),
	explosionSprite(explosion)
{

	for (int i = 0; i < MAX_PROJECTILES; i++) {
		CreateMoreProjectiles();
	}

	fireRate = FireRate;
	desiredTime = 0;
	currentTime = 0;
}

void Spawner::AddToPool(Projectile* const& entity)
{
	entity->SetActive(false);

	poolOfProjectiles.push_back(entity);
}

Spawner::~Spawner()
{
	poolOfProjectiles.removeAll();
	updateObjects.removeAll();
	delete pos;
	delete dir;

}

void Spawner::CreateMoreProjectiles()
{
	Projectile* entity = new Projectile(*pos + *dir * OFFSET, *dir, toSpawn, explosionSprite);
	updateObjects.push_back(entity);
	AddToPool(entity);
}



void Spawner::Spawn()
{
	if (poolOfProjectiles.getCount() == 0)
		CreateMoreProjectiles();
	Projectile* entity = poolOfProjectiles.get(poolOfProjectiles.getCount() - 1);
	entity->SetActive(true);
	entity->Init((*pos) + (*dir), *dir);

	poolOfProjectiles.pop_back();

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
			Spawn();
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

	auto active = std::string("Bullets active:" + std::to_string(updateObjects.getCount() - poolOfProjectiles.getCount()));

	screen->Print(active.c_str(), 10, 20, 0xffffffff);
	for (int i = 0; i < updateObjects.getCount(); i++)
		updateObjects.get(i)->Render(screen);
}

