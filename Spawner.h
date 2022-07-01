#pragma once
#include "vector.h"
#include "Projectile.h"
#include "Entity.h"
#include "ExplosionBullet.h"

#include "PosDir.h"

#include "Callable.h"

class Spawner :public Updateable, public Renderable {
public:
	Spawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Tmpl8::Sprite* toSpawn, Tmpl8::Sprite* explosion, float FireRate = 1.0f);
	static void AddProjectileToPool(Projectile* entity);
	static void AddExplosionToPool(ExplosionBullet* entity);

	~Spawner();
	void CreateMoreProjectiles();
	void CreateMoreExplosions();
	void SpawnProjectiles();
	static void SpawnExplosions(Tmpl8::vec2 pos);

	void setFlag(bool fire);

	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
	static vector<Projectile*> poolOfProjectiles;
	static vector<ExplosionBullet*> poolOfExplosions;
private:
	float fireRate = 1.0f, currentTime, desiredTime;
	vector<Entity*> updateObjects;

	bool isSpawning = false;
	static bool isInit;
	Tmpl8::Sprite* toSpawn;
	Tmpl8::Sprite* explosionSprite;

	Tmpl8::vec2* dir;
	Tmpl8::vec2* pos;

	const float OFFSET = 20.0f;
	const int MAX_PROJECTILES = 10;
	const int MAX_EXPLOSIONS = 10;
};
