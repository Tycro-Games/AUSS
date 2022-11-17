#pragma once
#include "nlohmann_json/single_include/nlohmann/json.hpp"
#include "Subject.h"
#include "Wave.h"
#include "EnemySpawner.h"
class Enemy;
using json = nlohmann::json;
class EnemyWaveSpawner : public Spawner, public Subject, public Callable
{
public:
	EnemyWaveSpawner(Being* player);
	~EnemyWaveSpawner();
	void AddEnemyToPool(Enemy* enemy, bool isDead = false);
	Enemy* CreateEnemy(EnemyTypes enemyType);
	void SetJsonValues(Enemy* enemy, json& enemyJson);
	void CreateMoreEnemies(EnemyTypes enemy);
	void PlayerTakesDamage(Enemy* enemy);
	void SpawnCurrentWave();
	void CheckThePossibleEnemies(size_t weight, std::vector<EnemyTypes>& possibleEnemies);
	Enemy* SpawnEnemy(Tmpl8::vec2, EnemyTypes enemies);
	// Inherited via Renderable
	virtual void Render(Tmpl8::Surface* screen) override;
	// Inherited via Updateable
	virtual void Update(float deltaTime) override;


	bool EnemyWaveSpawner::IsPoolEmpty(pool<Enemy*>& pool);
	const Tmpl8::vec2 EnemyWaveSpawner::GetPlayerPos()const;
	EnemyTypes ConvertToEnum(std::string str);
private:
	bool startedWave = false;
	void ThrowError(const char*);
	void EnemyInit();
	void InitializeSpawners();
	void ReadWaves();
	size_t indexSpawn;
	Timer timer;
	Being* player;
	Tmpl8::Sprite* hoarderSprite;
	Tmpl8::Sprite* runnerSprite;
	//Enemy Hoarder
	pool<Enemy*> poolOfHoarders;
	//Enemy Runner
	pool<Enemy*> poolOfRunners;

	std::vector<Collider*> activeColliders;
	std::vector<EnemySpawner*> enemySpawners;
	std::vector<EnemyTypes>enemiesToSpawn;


	Wave waves[10000];
	size_t indexWave = 0;
	size_t wavesCount = 0;
	//prototypes
	Enemy* enemyPrototypes[NUMBER_OF_ENEMIES];
	EnemyTypes allEnemyTypes[NUMBER_OF_ENEMIES] = { Hoarder,Runner };
	RandomNumbers randomNumbers;
	//consts
	const float SPAWNERS_XPOS_MULTIPLIERS = 0.88f;
	const float SPAWNERS_YPOS_MULTIPLIERS = 0.83f;
	const std::filesystem::path spriteExplosionPath = "assets/OriginalAssets/smoke.tga";


	// Inherited via Callable
	virtual void Call() override;

};
inline bool EnemyWaveSpawner::IsPoolEmpty(pool<Enemy*>& pool) {
	return pool.getCount() == 0;
}
inline const Tmpl8::vec2 EnemyWaveSpawner::GetPlayerPos() const
{
	return player->pos;
}

inline EnemyTypes EnemyWaveSpawner::ConvertToEnum(std::string str)
{
	EnemyTypes type = NUMBER_OF_ENEMIES;
	if (str == "Hoarder")
		type = Hoarder;
	else if (str == "Runner")
		type = Runner;
	if (type == NUMBER_OF_ENEMIES)
		ThrowError(str.c_str());
	return type;
}
