#include "EnemySpawner.h"
#include "EnemyHoarder.h"


EnemySpawner::EnemySpawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Being* player, Tmpl8::Sprite* toSpawn) :
	Spawner(pos, dir),
	player(player),
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
	poolOfEnemies.AddElement(enemy);

}

void EnemySpawner::CreateMoreEnemies()
{
	Enemy* enemy = new EnemyHoarder(PosDir(*pos + *dir * OFFSET, *dir), enemySprite, this);
	updateObjects.push_back(enemy);

	AddEnemyToPool(enemy);
}

void EnemySpawner::Update(float deltaTime)
{
	//if (timer->isUpdateable)
	//	timer->Update(deltaTime);

	for (int i = 0; i < updateObjects.getCount(); i++)
		updateObjects[i]->Update(deltaTime);
}

Tmpl8::vec2 EnemySpawner::GetPlayerPos()
{
	return *(player->pos);
}

void EnemySpawner::Render(Tmpl8::Surface* screen)
{
	for (int i = 0; i < updateObjects.getCount(); i++)
		updateObjects[i]->Render(screen);
}

void EnemySpawner::Call()
{
	if (poolOfEnemies.getCount() == 0)
		CreateMoreEnemies();
	Enemy* enemy = poolOfEnemies.PopElement();
	enemy->Init(PosDir(*pos, *dir));
	std::cout << "Spawn Enemy\n";
}
