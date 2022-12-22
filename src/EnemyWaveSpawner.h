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
	EnemyWaveSpawner();
	~EnemyWaveSpawner() override;

	void Init();
	/**
	 * \brief Adds an enemy to the pools and increases the score if the player killed it.
	 * \param enemy The enemy to be added to the pool.
	 * \param getPoints If the score should be added.
	 */
	void AddEnemyToPool(Enemy* enemy, bool getPoints = false);
	/**
	 * \brief Creates a new enemy of the specified type.
	 * \param enemyType Type of enemy to be created.
	 * \return A pointer to the new enemy created.
	 */
	Enemy* CreateEnemyPrototypes(EnemyTypes enemyType);
	/**
	 * \brief Initialize the prototypes to their values from their json file.
	 * \param enemy Enemy prototype that needs to be initialized.
	 * \param enemyJson The json file corresponding to the enemy.
	 */
	static void SetJsonValues(Enemy* enemy, json& enemyJson);
	/**
	 * \brief Makes a copy of the prototype type specified as a parameter.
	 * \param enemy The enemy type that should be cloned.
	 */
	void CloneEnemy(EnemyTypes enemy);
	/**
	 * \brief The player takes damage from the enemy parameter.
	 * \param enemy Enemy that hit the player.
	 */
	void PlayerTakesDamage(const Enemy* enemy);

	void SpawnEnemy(PosDir posDir, EnemyTypes enemy);
	// Inherited via Renderable
	void Render(Tmpl8::Surface* screen) override;
	// Inherited via Updateable
	void Update(float deltaTime) override;


	//this is the minimum distance to the player added to half of the collider of the enemy using this
	float getMaxPlayerDistanceSquared() const;

private:
	static EnemyTypes ConvertToEnum(const std::string& str);
	/**
	 * \brief updates the list of the enemies that could be spawned with the remaining weight of the wave.
	 */
	void GetEnemiesForCurrentWave();
	/**
	 * \brief Auxiliary method for the GetEnemiesForCurrentWave.
	 * \param weight Weight that enemies' weight should not be higher.
	 * \param possibleEnemies The list of the possible enemies to choose from.
	 */
	void CheckThePossibleEnemies(size_t weight, std::vector<EnemyTypes>& possibleEnemies) const;
	//add all the spawners that are offscreen
	void CheckTheOffscreenSpawners(std::vector<EnemySpawner*>& possibleSpawner) const;
	//init/reset methods
	void InitializeSpawners();
	void EnemyInit();
	void ReadWaves();
	void ClearVecOfPointers();
	static void ClearPoolOfEnemies(std::vector<Enemy*>& pool);
	/**
	 * \brief borrowed from template for errors
	 */
	static void ThrowError(const char*);
	//booleans for checking the state
	bool startedWave = false;
	bool firstWave = true;
	bool playerHasTakenDamage = false;
	//wave spawning
	void SpawnCurrentWave();
	size_t indexOfEnemiesToSpawn;
	Wave waves[10000];
	size_t indexWave;
	size_t wavesCount;
	Timer timeBetweenWaves;
	//sprites for enemies
	Tmpl8::Sprite hoarderSprite;
	Tmpl8::Sprite runnerSprite;
	Tmpl8::Sprite shooterSprite;
	Tmpl8::Sprite shielderSprite;
	//pools of the enemies
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
	std::vector<EnemyTypes> enemiesToSpawn;

	//score related variables
	unsigned int minimumProjectiles;
	unsigned int bonusWeight;
	unsigned int stepWeight = 1;
	//prototypes
	Enemy* enemyPrototypes[EnemyTypes::NUMBER_OF_ENEMIES] = {}; // NOLINT(clang-diagnostic-unused-private-field)
	RandomNumbers rng;
	//consts
	const float SPAWNERS_X_POS_MULTIPLIERS = 0.7f;
	const float SPAWNERS_Y_POS_MULTIPLIERS = 0.55f;
	const float SPAWNING_INTERVAL = .3f;
	float playerDistanceSqr = 0.0f;
	const std::filesystem::path spriteExplosionPath = "assets/OriginalAssets/smoke.tga";
};


inline EnemyTypes EnemyWaveSpawner::ConvertToEnum(const std::string& str)
{
	auto type = EnemyTypes::NUMBER_OF_ENEMIES;

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
