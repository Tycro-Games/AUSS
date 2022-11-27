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
	Spawner(const std::filesystem::path& explosion, unsigned int numberOfFrames = 10);
	Spawner(Tmpl8::Sprite* explosion);
	virtual ~Spawner();
	void AddExplosionToPool(ExplosionBullet* entity);
	void CreateMoreExplosions();
	void SpawnExplosions(Tmpl8::vec2 pos);

protected:
	void ResetExplosions();
	RandomNumbers randomNumbers;
	//to update
	std::vector<Entity*> updateObjects;
	std::vector<ExplosionBullet*> poolOfExplosions;
	//assets 
	Tmpl8::Sprite* explosionSprite;


	//consts
	const float OFFSET = 20.0f;
	const float MIN_DEVIATION = -.1f;
	const float MAX_DEVIATION = .1f;
private:

};

