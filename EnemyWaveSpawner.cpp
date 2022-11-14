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
	timer.Init(this, 1.0f);
	//enemy prototypes intialization
	EnemyInit();
	InitializeSpawners();
	ReadWaves();

}

void EnemyWaveSpawner::EnemyInit()
{
	hoarderSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/OriginalAssets/phaser.tga"), 16);
	runnerSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/OriginalAssets/sniper.tga"), 32);
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++) {
		enemyPrototypes[i] = CreateEnemy(allEnemyTypes[i]);
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
	wavesCount = wavesInput["waves"].size();
	for (int i = 0; i < wavesInput["waves"].size(); i++) {
		waves[i].weight = wavesInput["waves"][i].at("weight");

		//check if weight is valid
		if (waves[i].weight <= 0)
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

void EnemyWaveSpawner::Call()
{
	if (!startedWave)
		SpawnCurrentWave();
	else {
		SpawnEnemy(enemySpawners[(indexSpawn) % enemySpawners.getCount()]->GetSpawnerPos(), enemiesToSpawn[indexSpawn]);
		std::cout << indexSpawn << " ";
		indexSpawn++;
		if (enemiesToSpawn.getCount() == indexSpawn) {
			timer.isFinished = true;
			startedWave = false;
		}
	}
}

EnemyWaveSpawner::~EnemyWaveSpawner()
{
	for (size_t i = 0; i < NUMBER_OF_ENEMIES; i++) {
		delete enemyPrototypes[i];
	}
	//deleted by the above statement
	/*delete hoarderSprite;
	delete runnerSprite;*/
}
void EnemyWaveSpawner::PlayerTakesDamage(Enemy* enemy)
{
	player->TakeDamage(enemy->getDg());
}
void EnemyWaveSpawner::SpawnCurrentWave() {
	startedWave = true;
	int weight = waves[indexWave].weight;
	enemiesToSpawn.removeAll();
	dynamic_array<EnemyTypes>possibleEnemies;

	CheckThePossibleEnemies(weight, possibleEnemies);

	while (weight != 0) {

		size_t index;
		//if there are more than one enemy
		if (possibleEnemies.getCount() > 1)
			index = static_cast<size_t>(randomNumbers.RandomBetweenInts(0, static_cast<int>(possibleEnemies.getCount())));
		else
			index = 0;
		std::cout << index << ' ';
		EnemyTypes type = possibleEnemies[index];
		enemiesToSpawn.push_back(type);

		weight -= enemyPrototypes[type]->getWeight();
		//recheck the possible enemies
		CheckThePossibleEnemies(weight, possibleEnemies);
	}
	//interval for spawninig
	timer.Init(this, .15f, true);
	//spawn enemies in the spawners' positons
	indexSpawn = 0;


	std::cout << "index done\n";
}
void EnemyWaveSpawner::CheckThePossibleEnemies(size_t weight, dynamic_array<EnemyTypes>& possibleEnemies)
{
	possibleEnemies.removeAll();
	for (size_t i = 0; i < waves[indexWave].enemiesInWave.getCount(); i++) {
		//checks if the enemy weight is bigger the the weight of the entire wave
		if (enemyPrototypes[waves[indexWave].enemiesInWave[i]]->getWeight() <= weight)
			possibleEnemies.push_back(waves[indexWave].enemiesInWave[i]);
	}
}
Enemy* EnemyWaveSpawner::SpawnEnemy(Tmpl8::vec2 pos, EnemyTypes enemy)
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
		if (IsPoolEmpty(poolOfRunners))
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

		Tmpl8::vec2 randomDir = GetDirDeviation();
		//set position to the spawner's

		enemyToSpawn->Init(PosDir{ pos ,randomDir });
		Tmpl8::Game::AddCollider(enemyToSpawn->getColl());
		Tmpl8::Game::AddMoveable(enemyToSpawn->getMoveable());

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
	timer.Update(deltaTime);
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
	enemy->SetActive(false);
	activeColliders.remove(enemy->getColl());
	if (isDead) {
		notify(enemy->getScore(), Additive);
		if (activeColliders.getCount() == 0)
			SpawnCurrentWave();
	}
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
Enemy* EnemyWaveSpawner::CreateEnemy(EnemyTypes enemyType) {

	std::ifstream f;
	json enemyJson;
	Enemy* enemy = nullptr;
	switch (enemyType)
	{
	case Hoarder:
		f.open("json/Hoarder.json");
		enemy = new EnemyHoarder(PosDir(Tmpl8::vec2(0), Tmpl8::vec2(0)), hoarderSprite, this);
		enemyJson = json::parse(f);

		SetJsonValues(enemy, enemyJson);

		break;
	case Runner:
		f.open("json/Runner.json");

		enemy = new EnemyRunner(PosDir(Tmpl8::vec2(0), Tmpl8::vec2(0)), runnerSprite, this);
		enemyJson = json::parse(f);

		SetJsonValues(enemy, enemyJson);
		break;
	default:
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
}
void EnemyWaveSpawner::CreateMoreEnemies(EnemyTypes enemyType)
{
	Enemy* enemy = nullptr;
	switch (enemyType)
	{
		//add the json values t
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
