#pragma once
#include <vector>
#include "Projectile.h"
#include "Entity.h"


#include "Callable.h"

class Spawner :public Updateable, public Renderable {
public:
	Spawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, float FireRate = 1.0f);
	static void AddToPool(Projectile* const& entity);
	~Spawner();

	void Spawn();

	void setFlag(bool fire);



	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
	static std::vector<Projectile*> poolOfObjects;
private:
	float fireRate = 1.0f, currentTime, desiredTime;
	std::vector<Projectile*> updateObjects;

	Tmpl8::Sprite* toSpawn;
	bool isSpawning = false;
	Tmpl8::vec2* dir;
	Tmpl8::vec2* pos;
	const float OFFSET = 20.0f;
	const int MAX_PROJECTILES = 10;


};
