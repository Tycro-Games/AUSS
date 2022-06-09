#include "Spawner.h"
#include <iostream>
Spawner::Spawner(Tmpl8::Sprite* toSpawn, Tmpl8::vec2* pos, Tmpl8::vec2* dir, float FireRate)
	:toSpawn(toSpawn),
	pos(pos),
	dir(dir)
{
	fireRate = FireRate;
	desiredTime = 0;
	currentTime = 0;
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
	Projectile* pro = new Projectile(toSpawn, pos, *dir);

	poolOfObjects.push_back(pro);
	std::cout << currentTime << " " << desiredTime << "\n";
}

void Spawner::setFlag(bool fire)
{
	isSpawning = fire;
}


void Spawner::Update(float deltaTime)
{
	for (auto a : poolOfObjects)
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
	for (auto a : poolOfObjects)
		a->Render(screen);
}

