#pragma once
#include "Spawner.h"


class Projectile;

class ProjectileSpawner : public Spawner {

public:
	ProjectileSpawner(const Tmpl8::vec2 offset, const std::filesystem::path& _projectileSprite, const  std::filesystem::path& _explosionSprite);
	void Init();
	~ProjectileSpawner();

	void ChangeFireSpeed(float speed);
	void AddProjectileToPool(Projectile* entity);

	void CreateMoreProjectiles();

	void SpawnProjectiles();
	void AddProjectilesCount();
	void setFlag(bool fire);


	// Inherited via Entity
	void Update(float deltaTime) override;
	void Render(Tmpl8::Surface* screen) override;
	float fireRate = 1.0f, currentTime, desiredTime;

	const Tmpl8::vec2 offset;

	unsigned int getWaveProjectiles() const;
	unsigned int getTotalProjectiles() const;
	void ResetWaveProjectiles();
private:

	std::vector<Projectile*> poolOfProjectiles;

	bool poolsAreEmpty = true;
	bool isSpawning = false;
	//assets for projectiles
	Tmpl8::Sprite projectileSprite;
	//shot in total
	unsigned int totalProjectiles = 0;
	//shot int the current wave
	unsigned int waveProjectiles = 0;
	//consts
	const float FIRE_RATE = 0.25f;
	const float MIN_RATE = 0.2f;
	const float MAX_RATE = 2.0f;
	const float OFFSET_MULTIPLIER = 10.0f;
	//direction random

	const int MAX_PROJECTILES = 50;
	const int MAX_EXPLOSIONS = 5;


};
