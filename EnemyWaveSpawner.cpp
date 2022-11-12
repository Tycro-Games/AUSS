#include "EnemyWaveSpawner.h"
#include <iostream>

#include "EnemyHoarder.h"
#include "EnemyRunner.h"

#include "game.h"
namespace Tmpl8 {
	void NotifyUser(char* s);
}
EnemyWaveSpawner::EnemyWaveSpawner(Being* player, Tmpl8::Sprite* spriteExplosion)
	:Spawner(spriteExplosion),
	player(player)
{
	//enemy sprite intialization
	EnemyInit();
	InitializeSpawners();
	ReadWaves();
}

void EnemyWaveSpawner::EnemyInit()
{
	hoarderSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/OriginalAssets/phaser.tga"), 16);
	runnerSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/OriginalAssets/sniper.tga"), 32);
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++) {
		CreateEnemy(allEnemyTypes[i], enemyPrototypes[i]);
	}
}

void EnemyWaveSpawner::InitializeSpawners()
{
	//place the spawners in the four corners of the map
	Tmpl8::vec2 center = Tmpl8::vec2(ScreenWidth / 2, ScreenHeight / 2);
	float xOffset = SPAWNERS_XPOS_MULTIPLIERS * ScreenWidth;
	float yOffset = SPAWNERS_YPOS_MULTIPLIERS * ScreenHeight;

	enemySpawners.push_back(new EnemySpawner(new Tmpl8::vec2(center + Tmpl8::vec2(xOffset, yOffset)), this, explosionSprite));
	enemySpawners.push_back(new EnemySpawner(new Tmpl8::vec2(center + Tmpl8::vec2(xOffset, -yOffset)), this, explosionSprite));
	enemySpawners.push_back(new EnemySpawner(new Tmpl8::vec2(center + Tmpl8::vec2(-xOffset, yOffset)), this, explosionSprite));
	enemySpawners.push_back(new EnemySpawner(new Tmpl8::vec2(center + Tmpl8::vec2(-xOffset, -yOffset)), this, explosionSprite));
}
void EnemyWaveSpawner::ReadWaves()
{
	std::ifstream f("json/enemy_waves.json");
	json  wavesInput = json::parse(f);
	std::cout << "json parsed successfully\n";

	for (int i = 0; i < wavesInput["waves"].size(); i++) {
		waves[i].weight = wavesInput["waves"][i].at("weight");
		//check if weight is valid
		if (waves[i].weight < 0)
			ThrowError("weight must be a positive integer");
		for (int j = 0; j < wavesInput["waves"][i].at("enemy_types").size(); j++) {

			//check if enum is valid and avoid duplicates
			waves[i].enemiesInWave.push_unique(ConvertToEnum(wavesInput["waves"][i].at("enemy_types")[j]));
		}

	}

	/*for (int i = 0; i < wavesInput["waves"].size(); i++) {
		std::cout << waves[i].weight << "\n";
		for (int j = 0; j < waves[i].enemiesInWave.getCount(); j++)
			std::cout << waves[i].enemiesInWave[j] << " ";
		std::cout << '\n';
	}*/
}

EnemyWaveSpawner::~EnemyWaveSpawner()
{
	delete hoarderSprite;
	delete runnerSprite;
	delete[] enemyPrototypes;
}
void EnemyWaveSpawner::PlayerTakesDamage(Enemy* enemy)
{
	player->TakeDamage(enemy->getDg());
}
void EnemyWaveSpawner::SpawnCurrentWave() {
	int weight = waves[indexWave].weight;
	dynamic_array<EnemyTypes>enemiesToSpawn;
	dynamic_array<EnemyTypes>possibleEnemies;
	for (size_t i = 0; i < waves[indexWave].enemiesInWave.getCount(); i++)

		possibleEnemies.push_back(waves[indexWave].enemiesInWave[i]);

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
		break;
	}

	if (enemy == NUMBER_OF_ENEMIES)
		ThrowError("enemy spawner was not initialized");
	else if (enemyToSpawn) {
		activeColliders.push_back(enemyToSpawn->getColl());
	}
	return enemyToSpawn;
}

void EnemyWaveSpawner::Render(Tmpl8::Surface* screen)
{
	for (int i = 0; i < enemySpawners.getCount(); i++) {
		enemySpawners[i]->Render(screen);
		screen->Box(static_cast<int>(enemySpawners[i]->GetSpawnerPos().x), static_cast<int>(enemySpawners[i]->GetSpawnerPos().y), static_cast<int>(enemySpawners[i]->GetSpawnerPos().x) + 5, static_cast<int>(enemySpawners[i]->GetSpawnerPos().y) + 5, 0xFF0000);
	}

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
void EnemyWaveSpawner::CreateEnemy(EnemyTypes enemyType, Enemy* enemy) {
	switch (enemyType)
	{
	case Hoarder:
		enemy = new EnemyHoarder(PosDir(Tmpl8::vec2(0), Tmpl8::vec2(0)), hoarderSprite, this);

		break;
	case Runner:
		enemy = new EnemyRunner(PosDir(Tmpl8::vec2(0), Tmpl8::vec2(0)), runnerSprite, this);

		break;
	default:
		ThrowError("The creation of the enemy has failed");
		break;
	}
}
void EnemyWaveSpawner::CreateMoreEnemies(EnemyTypes enemyType)
{
	Enemy* enemy = nullptr;
	switch (enemyType)
	{
	case Hoarder:
		enemy = enemyPrototypes[Hoarder]->clone();
		break;
	case Runner:
		enemy = enemyPrototypes[Runner]->clone();

		break;
	default:
		ThrowError("The creation of the enemy has failed");
		break;
	}
	updateObjects.push_back(enemy);

	AddEnemyToPool(enemy);
}

void EnemyWaveSpawner::ThrowError(const char* place) {
	char t[128];
	sprintf(t, "Invalid json: %s", place);
	Tmpl8::NotifyUser(t);
}
