#pragma once
#include "nlohmann_json/single_include/nlohmann/json.hpp"
#include "vector.h"
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
	void CreateMoreEnemies(EnemyTypes enemy);
	void PlayerTakesDamage(Enemy* enemy);
	void ThrowError(const char*);
	Enemy* SpawnEnemy(Tmpl8::vec2, EnemyTypes enemies);
	// Inherited via Renderable
	virtual void Render(Tmpl8::Surface* screen) override;
	// Inherited via Updateable
	virtual void Update(float deltaTime) override;


	bool IsEnemy(Collider* col);
	bool EnemyWaveSpawner::IsPoolEmpty(pool<Enemy*>& pool);
	Tmpl8::vec2 EnemyWaveSpawner::GetPlayerPos();
	EnemyTypes ConvertToEnum(std::string str) {
		EnemyTypes type{};
		if (str == "Hoarder")
			type = Hoarder;
		else if (str == "Runner")
			type = Runner;
		return type;
	}
private:
	void InitializeSpawners();
	void ReadWaves();

	Being* player;
	Tmpl8::Sprite* hoarderSprite;
	Tmpl8::Sprite* runnerSprite;
	//Enemy Hoarder
	pool<Enemy*> poolOfHoarders;
	//Enemy Runner
	pool<Enemy*> poolOfRunners;

	vector<Entity*> updateObjects;

	vector<Collider*> activeColliders;
	vector<EnemySpawner*> enemySpawners;


	Wave waves[2];

};
inline bool EnemyWaveSpawner::IsPoolEmpty(pool<Enemy*>& pool) {
	return pool.getCount() == 0;
}
inline Tmpl8::vec2 EnemyWaveSpawner::GetPlayerPos()
{
	return player->pos;
}
