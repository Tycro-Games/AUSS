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
	void setFlag(bool fire);


	// Inherited via Entity
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;


private:
	float fireRate = 1.0f, currentTime, desiredTime;

	const Tmpl8::vec2 offset;

	pool<Projectile*> poolOfProjectiles;


	bool isSpawning = false;
	//assets for projectiles
	Tmpl8::Sprite projectileSprite;


	//consts
	const float FIRE_RATE = 0.25f;
	const float MIN_RATE = 0.2f;
	const float MAX_RATE = 2.0f;
	const float OFFSET_MULTIPLIER = 10.0f;
	//direction random

	const int MAX_PROJECTILES = 50;
	const int MAX_EXPLOSIONS = 5;

};
