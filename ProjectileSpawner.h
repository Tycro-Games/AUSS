#pragma once
#include "Spawner.h"
#include "ExplosionBullet.h"
#include "Projectile.h"

class Projectile;
class ExplosionBullet;
class ProjectileSpawner : public Spawner {

public:
	ProjectileSpawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Tmpl8::Sprite* toSpawn, Tmpl8::Sprite* explosion);
	~ProjectileSpawner();

	void ChangeFireSpeed(float speed);
	void AddProjectileToPool(Projectile* entity);
	void AddExplosionToPool(ExplosionBullet* entity);
	void CreateMoreProjectiles();
	void CreateMoreExplosions();
	void SpawnProjectiles();
	Tmpl8::vec2 GetDirDeviation();
	void SpawnExplosions(Tmpl8::vec2 pos);

	void setFlag(bool fire);


	// Inherited via Entity
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;


private:
	float fireRate = 1.0f, currentTime, desiredTime;


	pool<Projectile*> poolOfProjectiles;
	pool<ExplosionBullet*> poolOfExplosions;





	bool isSpawning = false;
	//assets for projectiles
	Tmpl8::Sprite* projectileSprite;
	Tmpl8::Sprite* explosionSprite;


	//consts
	const float FIRE_RATE = 0.25f;
	const float MIN_RATE = 0.2f;
	const float MAX_RATE = 2.0f;

	//direction random
	const float MIN_DEVIATION = -.1f;
	const float MAX_DEVIATION = .1f;
	float deviationMultiplier = 1.5f;

	const int MAX_PROJECTILES = 50;
	const int MAX_EXPLOSIONS = 5;

};
