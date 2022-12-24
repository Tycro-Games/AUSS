#pragma once

#include <vector>

#include "Entity.h"
#include "Collider.h"
#include "RandomNumbers.h"
#include "ExplosionBullet.h"
#include <filesystem>

class Spawner : public Updateable, public Renderable
{
public:
	explicit Spawner(const std::filesystem::path& explosion, unsigned int numberOfFrames = 10);
	~Spawner() override;
	//Deactivates explosion and adds it to the pool.
	void AddExplosionToPool(ExplosionBullet* entity);
	//Creates new explosions that will be added to the pool.
	void CreateMoreExplosions();
	//Spawns an explosion at the pos vector.
	void SpawnExplosions(Tmpl8::vec2 pos);

protected:
	void ResetExplosions();
	RandomNumbers randomNumbers;
	//to update
	std::vector<Entity*> updateObjects;
	std::vector<ExplosionBullet*> poolOfExplosions;
	//assets 
	Tmpl8::Sprite explosionSprite;


	//consts
	const float OFFSET = 20.0f;
	const float MIN_DEVIATION = -.05f;
	const float MAX_DEVIATION = .05f;
};
