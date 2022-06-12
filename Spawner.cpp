#include "Spawner.h"
#include <iostream>
Spawner::Spawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, float FireRate)
	:pos(pos),
	dir(dir)
{
	toSpawn = new Tmpl8::Sprite(new Tmpl8::Surface("assets/missile_big.tga"), 32);
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
	Projectile* pro = new Projectile(*pos, *dir, toSpawn);

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

