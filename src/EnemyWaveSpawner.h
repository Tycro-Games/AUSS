#pragma once
#include "Subject.h"
#include "nlohmann_json/single_include/nlohmann/json.hpp"
#include "Wave.h"
#include "EnemySpawner.h"
#include "Player.h"
#include "PosDir.h"
class Enemy;
using json = nlohmann::json;
class EnemyWaveSpawner : public Spawner, public Subject
{
public:
	//sort this in a logical way
	//comment stuff in the header
	//get into xmldocs
	//hard to break the code
	EnemyWaveSpawner();
	~EnemyWaveSpawner() override;
	void Init();
	/**
	 * \brief
	 * \param enemy The enemy to be added to the pool.
	 * \param getPoints The score that should be added.
	 */
	void AddEnemyToPool(Enemy* enemy, bool getPoints = false);
	Enemy* CreateEnemy(EnemyTypes enemyType);
	static void SetJsonValues(Enemy* enemy, json& enemyJson);
	void CreateMoreEnemies(EnemyTypes enemy);
	void PlayerTakesDamage(const Enemy* enemy);
	void GetEnemiesForCurrentWave();
	void CheckThePossibleEnemies(size_t weight, std::vector<EnemyTypes>& possibleEnemies) const;
	//add all the spawners that are offscreen
	void CheckTheOffscreenSpawners(std::vector<EnemySpawner*>& possibleSpawner) const;
	void SpawnEnemy(PosDir posDir, EnemyTypes enemy);
	// Inherited via Renderable
	void Render(Tmpl8::Surface* screen) override;
	// Inherited via Updateable
	void Update(float deltaTime) override;

	bool IsPoolEmpty(const std::vector<Enemy*>& pool) const;
	EnemyTypes ConvertToEnum(const std::string& str) const;

	//this is the minimum distance to the player added to half of the collider of the enemy using this
	float getMaxPlayerDistanceSquared()const;
private:
	static void ThrowError(const char*);
	void EnemyInit();
	void ClearVecOfPointers();
	void InitializeSpawners();
	void ReadWaves();
	static void ClearPoolOfEnemies(std::vector<Enemy*>& pool);
	bool startedWave = false;
	bool firstWave = true;
	size_t indexOfEnemiesToSpawn;
	Timer timer;
	bool playerHasTakenDamage = false;
	Tmpl8::Sprite hoarderSprite;
	Tmpl8::Sprite runnerSprite;
	Tmpl8::Sprite shooterSprite;
	Tmpl8::Sprite shielderSprite;
	//Enemy Hoarder
	std::vector<Enemy*> poolOfHoarders;
	//Enemy Runner
	std::vector<Enemy*> poolOfRunners;
	//Enemy Shooter
	std::vector<Enemy*> poolOfShooters;
	//Enemy Shielder
	std::vector<Enemy*> poolOfShielders;

	std::vector<Collider*> activeColliders;
	std::vector<EnemySpawner*> enemySpawners;
	std::vector<EnemyTypes>enemiesToSpawn;


	Wave waves[10000];
	size_t indexWave;
	size_t wavesCount;
	unsigned int minimumProjectiles;
	unsigned int bonusWeight;
	unsigned int stepWeight = 1;
	//prototypes
	Enemy* enemyPrototypes[EnemyTypes::NUMBER_OF_ENEMIES] = {};
	RandomNumbers rng;
	//consts
	const float SPAWNERS_X_POS_MULTIPLIERS = 0.7f;
	const float SPAWNERS_Y_POS_MULTIPLIERS = 0.55f;
	const float SPAWNING_INTERVAL = .3f;
	float playerDistanceSqr = 0.0f;
	const std::filesystem::path spriteExplosionPath = "assets/OriginalAssets/smoke.tga";

	void SpawnCurrentWave();

};

inline bool EnemyWaveSpawner::IsPoolEmpty(const std::vector<Enemy*>& pool) const {
	return pool.empty();
}

inline EnemyTypes EnemyWaveSpawner::ConvertToEnum(const std::string& str) const
{
	EnemyTypes type = EnemyTypes::NUMBER_OF_ENEMIES;

	if (str == "Hoarder")
		type = EnemyTypes::Hoarder;
	else if (str == "Runner")
		type = EnemyTypes::Runner;
	else if (str == "Shooter")
		type = EnemyTypes::Shooter;
	else if (str == "Shielder")
		type = EnemyTypes::Shielder;
	if (type == EnemyTypes::NUMBER_OF_ENEMIES)
		ThrowError(str.c_str());
	return type;
}

inline float EnemyWaveSpawner::getMaxPlayerDistanceSquared() const
{
	return playerDistanceSqr;
}
