#pragma once
#include "vector.h"
#include "Projectile.h"
#include "Entity.h"


#include "Callable.h"

class Spawner :public Updateable, public Renderable {
public:
	Spawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, Tmpl8::Sprite* toSpawn, float FireRate = 1.0f);
	static void AddToPool(Projectile* const& entity);
	~Spawner();
	void CreateMoreProjectiles();
	void Spawn();

	void setFlag(bool fire);

	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
	static vector<Projectile*> poolOfObjects;
private:
	float fireRate = 1.0f, currentTime, desiredTime;
	vector<Projectile*> updateObjects;

	bool isSpawning = false;
	Tmpl8::Sprite* toSpawn;
	Tmpl8::vec2* dir;
	Tmpl8::vec2* pos;

	const float OFFSET = 20.0f;
	const int MAX_PROJECTILES = 10;
};
