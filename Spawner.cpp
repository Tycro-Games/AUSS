#include "Spawner.h"
#include <iostream>
Spawner::Spawner(float FireRate)
{
	fireRate = FireRate;
	desiredTime = 0;
	currentTime = 0;
}

Spawner::~Spawner()
{
}

void Spawner::setFire(bool fire)
{
	isSpawning = fire;
}


void Spawner::Update(float deltaTime)
{
	if (currentTime >= desiredTime) {
		if (isSpawning) {
			std::cout << currentTime << " " << desiredTime << "\n";
			desiredTime = currentTime + fireRate;
		}
	}
	else
		currentTime += deltaTime;

}

