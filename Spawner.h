#pragma once
#include <deque>

#include "Entity.h"


class Spawner :public Updateable, public Renderable {
public:
	Spawner(Tmpl8::vec2* pos, Tmpl8::vec2* dir, float FireRate = 1.0f);
	~Spawner();
	void RemoveLastProjectile();
	void Spawn();
	void setFlag(bool fire);
	virtual void Update(float deltaTime) override;
	virtual void Render(Tmpl8::Surface* screen) override;
private:
	float fireRate = 1.0f, currentTime, desiredTime;
	std::deque<Entity*> poolOfObjects;
	Tmpl8::Sprite* toSpawn;
	bool isSpawning = false;
	Tmpl8::vec2* pos;
	Tmpl8::vec2* dir;
	// Inherited via Renderable


};
