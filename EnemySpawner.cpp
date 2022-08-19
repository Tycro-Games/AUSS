#include "EnemySpawner.h"



EnemySpawner::EnemySpawner(Tmpl8::vec2* pos, Tmpl8::Sprite* toSpawn) :
	Spawner(pos),
	enemySprite(toSpawn)
{
	timer = new Timer(this, timeToSpawn, true);
	Call();
}

EnemySpawner::~EnemySpawner()
{
	delete timer;
}

void EnemySpawner::AddEnemyToPool(Enemy* enemy)
{
	enemy->SetActive(false);

}

void EnemySpawner::Update(float deltaTime)
{
	if (timer->isUpdateable)
		timer->Update(deltaTime);

	for (int i = 0; i < updateObjects.getCount(); i++)
		updateObjects[i]->Update(deltaTime);
}

void EnemySpawner::Render(Tmpl8::Surface* screen)
{
	for (int i = 0; i < updateObjects.getCount(); i++)
		updateObjects[i]->Render(screen);
}

void EnemySpawner::Call()
{
	std::cout << "Spawn Enemy\n";
}
