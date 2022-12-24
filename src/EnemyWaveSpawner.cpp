#include "EnemyWaveSpawner.h"
#include <iostream>
#include <fstream>

#include "EnemyHoarder.h"
#include "EnemyRunner.h"
#include "EnemyShooter.h"
#include "EnemyShielder.h"

#include "game.h"
#include "Physics.h"
using namespace std;
using namespace Tmpl8;

namespace Tmpl8
{
	void NotifyUser(const char* s);
}

EnemyWaveSpawner::EnemyWaveSpawner()
	:
	Spawner("assets/OriginalAssets/smoke.tga"),
	indexOfEnemiesToSpawn(0),
	indexWave(0),
	wavesCount(0),
	hoarderSprite(new Surface("assets/hoarder.png"), 32),
	runnerSprite(new Surface("assets/runner.png"), 32),
	shooterSprite(new Surface("assets/shooter.png"), 1),
	shielderSprite(new Surface("assets/shielder.png"), 1),
	minimumProjectiles(0),
	bonusWeight(0)
{
}

void EnemyWaveSpawner::Init()
{
	minimumProjectiles = 0;
	bonusWeight = 0;
	indexOfEnemiesToSpawn = 0;
	indexWave = 0;
	wavesCount = 0;
	firstWave = true;
	timeBetweenWaves.Init(bind(&EnemyWaveSpawner::SpawnCurrentWave, this), 1.0f);
	//square distance to the player
	playerHalfRadiusSquared = Game::Get().getPlayer().getHalfCollider();
	playerHalfRadiusSquared *= playerHalfRadiusSquared;
	//enemy prototypes initializations
	EnemyInit();
	InitializeSpawners();
	ReadWaves();
}

void EnemyWaveSpawner::EnemyInit()
{
	ClearVecOfPointers();

	for (size_t i = 0; i < static_cast<size_t>(EnemyTypes::NUMBER_OF_ENEMIES); i++)
	{
		enemyPrototypes[i] = CreateEnemyPrototypes(static_cast<EnemyTypes>(i));
	}
}

void EnemyWaveSpawner::ClearVecOfPointers()
{
	for (size_t i = 0; i < updateObjects.size(); i++)
		if (updateObjects[i]->getUpdateable())
			delete updateObjects[i];
	updateObjects.clear();

	activeColliders.clear();

	ClearPoolOfEnemies(poolOfHoarders);
	ClearPoolOfEnemies(poolOfRunners);
	ClearPoolOfEnemies(poolOfShooters);
	ClearPoolOfEnemies(poolOfShielders);

	ResetExplosions();

	for (size_t i = 0; i < enemySpawners.size(); i++)
		delete enemySpawners[i];
	enemySpawners.clear();
	for (size_t i = 0; i < static_cast<size_t>(EnemyTypes::NUMBER_OF_ENEMIES); i++)
	{
		delete enemyPrototypes[i];
	}
}


void EnemyWaveSpawner::ClearPoolOfEnemies(vector<Enemy*>& pool)
{
	for (size_t i = 0; i < pool.size(); i++)
		delete pool[i];
	pool.clear();
}

void EnemyWaveSpawner::InitializeSpawners()
{
	//place the spawners in the four corners of the map
	const auto center = vec2(ScreenWidth / 2.0f, ScreenHeight / 2.0f);
	const float xOffset = SPAWNERS_X_POS_MULTIPLIERS * ScreenWidth;
	const float yOffset = SPAWNERS_Y_POS_MULTIPLIERS * ScreenHeight;


	enemySpawners.push_back(new EnemySpawner(center + vec2(xOffset, yOffset)));
	enemySpawners.push_back(new EnemySpawner(center + vec2(-xOffset, yOffset)));
	enemySpawners.push_back(new EnemySpawner(center + vec2(xOffset, -yOffset)));
	enemySpawners.push_back(new EnemySpawner(center + vec2(-xOffset, -yOffset)));
}

void EnemyWaveSpawner::ReadWaves()
{
	std::ifstream f("json/enemy_waves.json");
	json wavesInput = json::parse(f);
	std::cout << "json parsed successfully\n";
	wavesCount = wavesInput["waves"].size();

	for (size_t i = 0; i < wavesCount; i++)
	{
		waves[i].weight = wavesInput["waves"][i].at("weight");

		//check if weight is valid
		if (waves[i].weight <= 0)
			ThrowError("weight must be a positive integer");
		for (size_t j = 0; j < wavesInput["waves"][i].at("enemy_types").size(); j++)
		{
			//check if enum is valid and avoid duplicates
			EnemyTypes t = ConvertToEnum(wavesInput["waves"][i].at("enemy_types")[j]);
			if (find(waves[i].enemiesInWave.begin(), waves[i].enemiesInWave.end(), t) == waves[i].enemiesInWave.end())
				waves[i].enemiesInWave.push_back(t);
		}
	}
}

//spawns enemies at an interval for random numbers to use time as a seed
void EnemyWaveSpawner::SpawnCurrentWave()
{
	if (!startedWave)
		GetEnemiesForCurrentWave();
	else
	{
		//this must have a size that is bigger than 1
		vector<EnemySpawner*> possibleSpawners;
		CheckTheOffscreenSpawners(possibleSpawners);
		const size_t indexOfSpawner = static_cast<size_t>(rng.RandomBetweenInts(
			0, static_cast<int>(possibleSpawners.size())));
		//error if the assumption about spawners is not right
		assert(!possibleSpawners.empty() &&
			indexOfSpawner < possibleSpawners.size());

		SpawnEnemy(PosDir{ possibleSpawners[indexOfSpawner]->GetSpawnerPos(), 0 }, enemiesToSpawn[indexOfEnemiesToSpawn]);
		std::cout << "Enemy count:" << enemiesToSpawn.size() << '\n';
		indexOfEnemiesToSpawn++;
		//spawned the last enemy of the wave
		if (enemiesToSpawn.size() == indexOfEnemiesToSpawn)
		{
			firstWave = false;

			timeBetweenWaves.isFinished = true;
			startedWave = false;
		}
	}
}

EnemyWaveSpawner::~EnemyWaveSpawner()
{
	ClearVecOfPointers();
}

void EnemyWaveSpawner::PlayerTakesDamage(const Enemy* enemy)
{
	notify(static_cast<int>(enemy->getDg()), EventType::PlayerTakesDamage);
	playerHasTakenDamage = true;
}

void EnemyWaveSpawner::GetEnemiesForCurrentWave()
{
	startedWave = true;
	unsigned int weight = waves[indexWave].weight + bonusWeight;
	enemiesToSpawn.clear();
	vector<EnemyTypes> possibleEnemies;

	CheckThePossibleEnemies(weight, possibleEnemies);
	if (possibleEnemies.empty())
		ThrowError("Too small weight for spawning any enemies");
	while (weight != 0 && !possibleEnemies.empty())
	{
		size_t index;
		//if there are more than one enemy
		if (possibleEnemies.size() > 1)
			index = static_cast<size_t>(rng.RandomBetweenInts(0, static_cast<int>(possibleEnemies.size())));
		else
			index = 0;
		EnemyTypes type = possibleEnemies[index];
		enemiesToSpawn.push_back(type);

		weight -= static_cast<int>(enemyPrototypes[static_cast<size_t>(type)]->getWeight());
		//recheck the possible enemies
		CheckThePossibleEnemies(weight, possibleEnemies);
	}
	//interval for spawning
	timeBetweenWaves.Init(bind(&EnemyWaveSpawner::SpawnCurrentWave, this), SPAWNING_INTERVAL, true);
	//spawning interval could be fetched from the json per wave
	//spawn enemies in the spawners' positions
	indexOfEnemiesToSpawn = 0;
}

void EnemyWaveSpawner::CheckThePossibleEnemies(const size_t weight, vector<EnemyTypes>& possibleEnemies) const
{
	possibleEnemies.clear();
	for (size_t i = 0; i < waves[indexWave].enemiesInWave.size(); i++)
	{
		//checks if the enemy weight is bigger the the weight of the entire wave
		if (enemyPrototypes[static_cast<size_t>(waves[indexWave].enemiesInWave[i])]->getWeight() <= weight)
			possibleEnemies.push_back(waves[indexWave].enemiesInWave[i]);
	}
}

void EnemyWaveSpawner::CheckTheOffscreenSpawners(vector<EnemySpawner*>& possibleSpawner) const
{
	possibleSpawner.clear();
	for (size_t i = 0; i < enemySpawners.size(); i++)
	{
		if (!Physics::InGameScreen(enemySpawners[i]->GetSpawnerPos()))
			possibleSpawner.push_back(enemySpawners[i]);
	}
}

void EnemyWaveSpawner::SpawnEnemy(const PosDir posDir, const EnemyTypes enemy)
{
	Enemy* enemyToSpawn = nullptr;
	switch (enemy)
	{
	case EnemyTypes::Hoarder:
		if (poolOfHoarders.empty())
			CloneEnemy(enemy);
		enemyToSpawn = poolOfHoarders[poolOfHoarders.size() - 1];
		poolOfHoarders.pop_back();
		break;
	case EnemyTypes::Runner:
		if (poolOfRunners.empty())
			CloneEnemy(enemy);
		enemyToSpawn = poolOfRunners[poolOfRunners.size() - 1];
		poolOfRunners.pop_back();
		break;
	case EnemyTypes::Shooter:
		if (poolOfShooters.empty())
			CloneEnemy(enemy);
		enemyToSpawn = poolOfShooters[poolOfShooters.size() - 1];
		poolOfShooters.pop_back();
		break;
	case EnemyTypes::Shielder:
		if (poolOfShielders.empty())
			CloneEnemy(enemy);
		enemyToSpawn = poolOfShielders[poolOfShielders.size() - 1];
		poolOfShielders.pop_back();
		break;
	case EnemyTypes::NUMBER_OF_ENEMIES:
		ThrowError("could not spawn enemies");

		break;
	}

	if (enemyToSpawn)
	{
		if (enemyToSpawn->getEnemyType() != EnemyTypes::Runner)
		{
			//runner has a predefined lifetime
			minimumProjectiles += enemyToSpawn->getMaxHp() / enemyToSpawn->getDgToTake();
			std::cout << "Perfect count for projectiles:" << minimumProjectiles << "\n";
		}
		activeColliders.push_back(enemyToSpawn->getColl());
		//set position to the spawner's

		enemyToSpawn->Init(posDir);
		Game::Get().AddCollider(enemyToSpawn->getColl());
		Game::Get().AddMoveable(enemyToSpawn->getMoveable());
	}
}

void EnemyWaveSpawner::Render(Surface* screen)
{
#ifdef _DEBUG
	for (size_t i = 0; i < enemySpawners.size(); i++)
	{

		screen->Box(static_cast<int>(enemySpawners[i]->GetSpawnerPos().x),
			static_cast<int>(enemySpawners[i]->GetSpawnerPos().y),
			static_cast<int>(enemySpawners[i]->GetSpawnerPos().x) + 5,
			static_cast<int>(enemySpawners[i]->GetSpawnerPos().y) + 5, 0xFF0000);
	}
#endif

	for (size_t i = 0; i < updateObjects.size(); i++)
		updateObjects[i]->Render(screen);
}

void EnemyWaveSpawner::Update(const float deltaTime)
{
	timeBetweenWaves.Update(deltaTime);

	for (size_t i = 0; i < updateObjects.size(); i++)
		updateObjects[i]->Update(deltaTime);
}


void EnemyWaveSpawner::AddEnemyToPool(Enemy* enemy, const bool getPoints)
{
	enemy->SetActive(false);
	activeColliders.erase(remove(
		activeColliders.begin()
		, activeColliders.end(), enemy->getColl())
		, activeColliders.end());


	if (getPoints)
	{
		notify(static_cast<int>(enemy->getScore()), EventType::EnemyDeath);
	}
	if (activeColliders.empty())
	{
		//signal ending of this wave
		if (enemiesToSpawn.size() == indexOfEnemiesToSpawn)
		{
			//multiply the score if the player was not hit the previous wave 
			if (!playerHasTakenDamage)
			{
				notify(1, EventType::BonusConditions);
				std::cout << "Double points for health\n";
			}
			else
			{
				playerHasTakenDamage = false;
			}
			//notify the score 
			//number of minimum projectiles
			notify(static_cast<int>(minimumProjectiles), EventType::EndOfAWave);
			minimumProjectiles = 0;
			Game::Get().PlaySound(SoundID::endWave);
		}

		GetEnemiesForCurrentWave();
		//loop back to the beginning and add to the bonus weight
		indexWave++;
		if (indexWave == wavesCount)
		{
			indexWave = 0;
			bonusWeight += stepWeight;
		}
	}
	switch (enemy->getEnemyType())
	{
	case EnemyTypes::Hoarder:
		poolOfHoarders.push_back(enemy);
		break;
	case EnemyTypes::Runner:
		poolOfRunners.push_back(enemy);
		break;
	case EnemyTypes::Shooter:
		poolOfShooters.push_back(enemy);
		break;
	case EnemyTypes::Shielder:
		poolOfShielders.push_back(enemy);
		break;
	case EnemyTypes::NUMBER_OF_ENEMIES:
		break;
	}
	//game wiring
	Game::Get().RemoveCollider(enemy->getColl());
	Game::Get().RemoveMoveable(enemy->getMoveable());
}

Enemy* EnemyWaveSpawner::CreateEnemyPrototypes(const EnemyTypes enemyType)
{
	std::ifstream f;
	json enemyJson;
	Enemy* enemy = nullptr;

	switch (enemyType)
	{
	case EnemyTypes::Hoarder:
		f.open("json/Hoarder.json");
		enemy = new EnemyHoarder(PosDir(vec2(0), vec2(0)), &hoarderSprite, this);
		enemyJson = json::parse(f);

		SetJsonValues(enemy, enemyJson);

		break;
	case EnemyTypes::Runner:
		f.open("json/Runner.json");

		enemy = new EnemyRunner(PosDir(vec2(0), vec2(0)), &runnerSprite, this);
		enemyJson = json::parse(f);

		SetJsonValues(enemy, enemyJson);
		break;
	case EnemyTypes::Shooter:
		f.open("json/Shooter.json");

		enemy = new EnemyShooter(PosDir(vec2(0), vec2(0)), &shooterSprite, this);
		enemyJson = json::parse(f);

		SetJsonValues(enemy, enemyJson);
		break;
	case EnemyTypes::Shielder:
		f.open("json/Shielder.json");

		enemy = new EnemyShielder(PosDir(vec2(0), vec2(0)), &shielderSprite, this);
		enemyJson = json::parse(f);

		SetJsonValues(enemy, enemyJson);
		break;
	case EnemyTypes::NUMBER_OF_ENEMIES:
		ThrowError("The creation of the enemy has failed");

		break;
	}
	return enemy;
}

void EnemyWaveSpawner::SetJsonValues(Enemy* enemy, json& enemyJson)
{
	enemy->setDg(enemyJson["dg"]);
	enemy->setHp(enemyJson["hp"]);
	enemy->setScore(enemyJson["score"]);
	enemy->setWeight(enemyJson["weight"]);
	enemy->setDgToTake(enemyJson["dgTake"]);
}

void EnemyWaveSpawner::CloneEnemy(const EnemyTypes enemyType)
{
	Enemy* enemy = nullptr;

	if (enemyType < EnemyTypes::NUMBER_OF_ENEMIES && enemyType >= EnemyTypes::Hoarder)
		enemy = enemyPrototypes[static_cast<size_t>(enemyType)]->clone();
	else
		ThrowError("The creation of the enemy has failed");
	updateObjects.push_back(enemy);

	AddEnemyToPool(enemy);
}

void EnemyWaveSpawner::ThrowError(const char* place)
{
	char t[128];
	sprintf(t, "Invalid json: %s", place); // NOLINT(cert-err33-c)
	NotifyUser(t);
}
