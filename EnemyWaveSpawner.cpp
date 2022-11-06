#include "EnemyWaveSpawner.h"
#include <iostream>

#include "EnemyHoarder.h"
#include "EnemyRunner.h"

#include "game.h"
EnemyWaveSpawner::EnemyWaveSpawner(Being* player, Tmpl8::Sprite* spriteExplosion)
	:Spawner(spriteExplosion),
	player(player)
{

	hoarderSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/OriginalAssets/phaser.tga"), 16);
	runnerSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/OriginalAssets/sniper.tga"), 32);
	std::ifstream f("enemy_waves.json");
	input = json::parse(f);
	for (json::iterator it = input.begin(); it != input.end(); ++it) {
		std::cout << it.key() << " : " << it.value() << "\n";
	}
	//place the spawners
	EnemySpawner* enemy = new EnemySpawner(new Tmpl8::vec2(ScreenWidth / 2, ScreenWidth / 2), this, explosionSprite);
	enemySpawners.push_back(enemy);
	enemy->SetEnemy(Hoarder);
}

EnemyWaveSpawner::~EnemyWaveSpawner()
{
	delete hoarderSprite;
	delete runnerSprite;
}
void EnemyWaveSpawner::PlayerTakesDamage(Enemy* enemy)
{
	player->TakeDamage(enemy->getDg());
}

Enemy* EnemyWaveSpawner::SpawnEnemy(Tmpl8::vec2, EnemyTypes enemy)
{
	//no more enemies of this type
	Enemy* enemyToSpawn = nullptr;
	switch (enemy)
	{
	case Hoarder:
		if (IsPoolEmpty(poolOfHoarders))
			CreateMoreEnemies(Hoarder);
		enemyToSpawn = poolOfHoarders.PopElement();
		break;
	case Runner:
		if (IsPoolEmpty(poolOfHoarders))
			CreateMoreEnemies(Runner);
		enemyToSpawn = poolOfRunners.PopElement();
		break;
	default:
		throw std::invalid_argument("something is wrong with the wave");
		break;
	}


	activeColliders.push_back(enemyToSpawn->getColl());

	return enemyToSpawn;
}

void EnemyWaveSpawner::Render(Tmpl8::Surface* screen)
{
	for (int i = 0; i < enemySpawners.getCount(); i++)
		enemySpawners[i]->Render(screen);

	for (int i = 0; i < updateObjects.getCount(); i++)
		updateObjects[i]->Render(screen);
}

void EnemyWaveSpawner::Update(float deltaTime)
{
	for (int i = 0; i < enemySpawners.getCount(); i++)
		enemySpawners[i]->Update(deltaTime);

	for (int i = 0; i < updateObjects.getCount(); i++)
		updateObjects[i]->Update(deltaTime);
}

bool EnemyWaveSpawner::IsEnemy(Collider* col)
{
	return activeColliders.contains(col);
}

void EnemyWaveSpawner::AddEnemyToPool(Enemy* enemy, bool isDead)
{
	if (isDead)
		notify(1, Additive);
	enemy->SetActive(false);
	activeColliders.remove(enemy->getColl());
	switch (enemy->GetEnemyType())
	{
	case Hoarder:
		poolOfHoarders.AddElement(enemy);
		break;
	case Runner:
		poolOfRunners.AddElement(enemy);
		break;
	default:
		break;
	}
	//game wiring
	Tmpl8::Game::RemoveCollider(enemy->getColl());
	Tmpl8::Game::RemoveMoveable(enemy->getMoveable());
}

void EnemyWaveSpawner::CreateMoreEnemies(EnemyTypes enemyType)
{
	Enemy* enemy = nullptr;
	switch (enemyType)
	{
	case Hoarder:
		enemy = new EnemyHoarder(PosDir(Tmpl8::vec2(0), Tmpl8::vec2(0)), hoarderSprite, this);
		break;
	case Runner:
		enemy = new EnemyHoarder(PosDir(Tmpl8::vec2(0), Tmpl8::vec2(0)), hoarderSprite, this);

		break;
	default:
		break;
	}
	updateObjects.push_back(enemy);

	AddEnemyToPool(enemy);
}
