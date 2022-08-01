#pragma once
#include "vector.h"
#include "Projectile.h"
#include "Entity.h"
#include "ExplosionBullet.h"
#include "CollisionDetection.h"
#include "PosDir.h"

#include "Callable.h"


class Projectile;
class ExplosionBullet;
class Spawner :public Updateable, public Renderable {

public:
	Spawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Tmpl8::Sprite* toSpawn, Tmpl8::Sprite* explosion);
	void ChangeFireSpeed(float speed);
	void AddProjectileToPool(Projectile* entity);
	void AddExplosionToPool(ExplosionBullet* entity);

	~Spawner();
	void CreateMoreProjectiles();
	void CreateMoreExplosions();
	void SpawnProjectiles();
	void SpawnExplosions(Tmpl8::vec2 pos);

	void setFlag(bool fire);

	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
	vector<Projectile*> poolOfProjectiles;
	vector<ExplosionBullet*> poolOfExplosions;
private:
	float fireRate = 1.0f, currentTime, desiredTime;
	vector<Projectile*> activeProjectiles;
	vector<Entity*> updateObjects;
	CollisionDetection colDec;

	bool isSpawning = false;

	Tmpl8::Sprite* toSpawn;
	Tmpl8::Sprite* explosionSprite;

	Tmpl8::vec2* dir;
	Tmpl8::vec2* pos;

	const float FIRE_RATE = 0.25f;
	const float MIN_RATE = 0.2f;
	const float MAX_RATE = 2.0f;
	const float OFFSET = 20.0f;

	const int MAX_PROJECTILES = 50;
	const int MAX_EXPLOSIONS = 5;

};
