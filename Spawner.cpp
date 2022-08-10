#include "Spawner.h"

#include <string>
#include <iostream>
//random number
#include <cstdlib>
#include <ctime>
Spawner::Spawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Tmpl8::Sprite* tospawn, Tmpl8::Sprite* explosion)
	:pos(pos),
	dir(dir),
	toSpawn(tospawn),
	explosionSprite(explosion),
	activeProjectiles(),
	colDec(ScreenWidth, activeProjectiles)
{
	SetSeed();
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
void Spawner::SetSeed()
{
	srand(time(0));
}
void Spawner::ChangeFireSpeed(float speed) {

	fireRate += speed;
	if (fireRate < MIN_RATE)
		fireRate = MIN_RATE;
	if (fireRate > MAX_RATE)
		fireRate = MAX_RATE;
}
void Spawner::AddProjectileToPool(Projectile* entity)
{
	entity->SetActive(false);
	activeProjectiles.remove(entity);
	poolOfProjectiles.push_back(entity);

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
	Projectile* entity = new Projectile(PosDir(*pos + *dir * OFFSET, *dir), toSpawn, this);
	updateObjects.push_back(entity);

	AddProjectileToPool(entity);

}
void Spawner::CreateMoreExplosions()
{
	ExplosionBullet* bullet = new ExplosionBullet(explosionSprite, this);
	updateObjects.push_back(bullet);

	AddExplosionToPool(bullet);
}

void Spawner::SpawnProjectiles()
{
	if (poolOfProjectiles.getCount() == 0)
		CreateMoreProjectiles();

	Projectile* projectile = poolOfProjectiles.get(poolOfProjectiles.getCount() - 1);

	Tmpl8::vec2 randomDir = GetDirDeviation();
	projectile->Init(PosDir{ (*pos) + (*dir), (*dir + randomDir).normalized() });

	activeProjectiles.push_back(projectile);
	poolOfProjectiles.pop_back();
}

Tmpl8::vec2 Spawner::GetDirDeviation()
{
	//random direction
	float x = MIN_DEVIATION + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX_DEVIATION - MIN_DEVIATION)));
	float y = MIN_DEVIATION + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MAX_DEVIATION - MIN_DEVIATION)));
	//adding multiplier
	x *= deviationMultiplier;
	y *= deviationMultiplier;
	return Tmpl8::vec2(x, y);
}

void Spawner::SpawnExplosions(Tmpl8::vec2 pos)
{
	if (poolOfExplosions.getCount() == 0)
		CreateMoreExplosions();
	ExplosionBullet* bullet = poolOfExplosions.get(poolOfExplosions.getCount() - 1);

	bullet->Init(pos);

	poolOfExplosions.pop_back();
}

void Spawner::setFlag(bool fire)
{
	isSpawning = fire;
}

void Spawner::Update(float deltaTime)
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

void Spawner::Render(Tmpl8::Surface* screen)
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
	for (int i = 0; i < updateObjects.getCount(); i++)
		updateObjects[i]->Render(screen);

}