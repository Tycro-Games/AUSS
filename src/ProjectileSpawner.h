#pragma once
#include "Spawner.h"


class Projectile;

class ProjectileSpawner : public Spawner
{
public:
	ProjectileSpawner(Tmpl8::vec2 offset, const std::filesystem::path& _projectileSprite,
		const std::filesystem::path& _explosionSprite);
	~ProjectileSpawner() override = default;

	void Init();

	void AddProjectileToPool(Projectile* entity);
	void SpawnProjectiles();

	void ResetWaveProjectiles();

	//setters
	void setShootingFlag(bool fire);
	//getters
	unsigned int getWaveProjectiles() const;
	unsigned int getTotalProjectiles() const;


	// Inherited via Entity
	void Update(float deltaTime) override;
	void Render(Tmpl8::Surface* screen) override;


	const Tmpl8::vec2 offset;

private:
	void CreateMoreProjectiles();

	//firerate related
	float fireRate = 1.0f, currentTime, desiredTime;
	std::vector<Projectile*> poolOfProjectiles;

	bool isSpawning = false;
	//assets for projectiles
	Tmpl8::Sprite projectileSprite;
	//shot in total
	unsigned int totalProjectiles = 0;
	//shot int the current wave
	unsigned int waveProjectiles = 0;
	//consts
	const float FIRE_RATE = 0.25f;
	const float OFFSET_MULTIPLIER = 10.0f;
	//pre-created projectiles and explosions
	const int MAX_PROJECTILES = 50;
	const int MAX_EXPLOSIONS = 5;
};
