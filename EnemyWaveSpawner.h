#pragma once
#include "nlohmann_json/single_include/nlohmann/json.hpp"
#include "dynamic_array.h"
#include "Subject.h"
#include "Wave.h"
#include "EnemySpawner.h"

#include <fstream>

class Enemy;
using json = nlohmann::json;
class EnemyWaveSpawner : public Spawner, public Subject
{
public:
	EnemyWaveSpawner(Being* player, Tmpl8::Sprite* explosion);
	~EnemyWaveSpawner();
	void AddEnemyToPool(Enemy* enemy, bool isDead = false);
	void CreateEnemy(EnemyTypes enemyType, Enemy* enemy);
	void CreateMoreEnemies(EnemyTypes enemy);
	void PlayerTakesDamage(Enemy* enemy);
	void SpawnCurrentWave();
	Enemy* SpawnEnemy(Tmpl8::vec2, EnemyTypes enemies);
	// Inherited via Renderable
	virtual void Render(Tmpl8::Surface* screen) override;
	// Inherited via Updateable
	virtual void Update(float deltaTime) override;


	bool IsEnemy(Collider* col);
	bool EnemyWaveSpawner::IsPoolEmpty(pool<Enemy*>& pool);
	Tmpl8::vec2 EnemyWaveSpawner::GetPlayerPos();
	EnemyTypes ConvertToEnum(std::string str);
private:
	void ThrowError(const char*);
	void EnemyInit();
	void InitializeSpawners();
	void ReadWaves();

	Being* player;
	Tmpl8::Sprite* hoarderSprite;
	Tmpl8::Sprite* runnerSprite;
	//Enemy Hoarder
	pool<Enemy*> poolOfHoarders;
	//Enemy Runner
	pool<Enemy*> poolOfRunners;

	dynamic_array<Entity*> updateObjects;

	dynamic_array<Collider*> activeColliders;
	dynamic_array<EnemySpawner*> enemySpawners;


	dynamic_array<Wave> waves;
	size_t indexWave = 0;
	//prototypes
	Enemy* enemyPrototypes[NUMBER_OF_ENEMIES];
	EnemyTypes allEnemyTypes[NUMBER_OF_ENEMIES] = { Hoarder,Runner };
	//consts
	const float SPAWNERS_XPOS_MULTIPLIERS = 0.88f;
	const float SPAWNERS_YPOS_MULTIPLIERS = 0.83f;

};
inline bool EnemyWaveSpawner::IsPoolEmpty(pool<Enemy*>& pool) {
	return pool.getCount() == 0;
}
inline Tmpl8::vec2 EnemyWaveSpawner::GetPlayerPos()
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
