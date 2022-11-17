#pragma once

#include <vector>
#include "pool.h"

#include "Entity.h"
#include "Collider.h"
#include "RandomNumbers.h"
#include "ExplosionBullet.h"
#include <filesystem>

class Spawner : public Updateable, public Renderable
{
public:
	Spawner(const std::filesystem::path& explosion);
	Spawner(const Tmpl8::Sprite& explosion);
	virtual ~Spawner();
	void AddExplosionToPool(ExplosionBullet* entity);
	void CreateMoreExplosions();
	void SpawnExplosions(Tmpl8::vec2 pos);
	Tmpl8::vec2 GetDirDeviation();

protected:
	RandomNumbers randomNumbers;
	//to update
	std::vector<Entity*> updateObjects;
	pool<ExplosionBullet*> poolOfExplosions;
	//assets 
	Tmpl8::Sprite explosionSprite;

	float deviationMultiplier = 1.5f;

	//consts
	const float OFFSET = 20.0f;
	const float MIN_DEVIATION = -.1f;
	const float MAX_DEVIATION = .1f;
private:

};

