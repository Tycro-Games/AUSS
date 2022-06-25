#include "Spawner.h"

#include <iostream>
std::vector <Projectile*> Spawner::poolOfObjects;
Spawner::Spawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, float FireRate)
	:pos(pos),
	dir(dir)
{
	toSpawn = new Tmpl8::Sprite(new Tmpl8::Surface("assets/missile_big.tga"), 32);
	for (int i = 0; i < MAX_PROJECTILES; i++) {
		Projectile* entity = new Projectile(*pos + *dir * OFFSET, *dir, toSpawn);
		updateObjects.push_back(entity);
		AddToPool(entity);
	}

	fireRate = FireRate;
	desiredTime = 0;
	currentTime = 0;
}

void Spawner::AddToPool(Projectile* const& entity)
{

	entity->SetRenderable(false);
	entity->SetUpdateable(false);
	poolOfObjects.push_back(entity);
}

Spawner::~Spawner()
{
	delete pos;
	delete dir;
	delete toSpawn;
	for (auto p : poolOfObjects)
		delete p;
	poolOfObjects.clear();

}



void Spawner::Spawn()
{
	Projectile* entity = poolOfObjects[poolOfObjects.size() - 1];
	entity->SetActive();
	entity->Init((*pos) + (*dir), *dir);
	poolOfObjects.pop_back();

}



void Spawner::setFlag(bool fire)
{
	isSpawning = fire;
}




void Spawner::Update(float deltaTime)
{
	for (auto a : updateObjects)
		a->Update(deltaTime);

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
	for (auto a : updateObjects)
		a->Render(screen);
}

