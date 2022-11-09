#pragma once

#include "vector.h"
#include "pool.h"

#include "Entity.h"
#include "Collider.h"
#include "RandomNumbers.h"
#include "ExplosionBullet.h"

class Spawner : public Updateable, public Renderable
{
public:
	Spawner(Tmpl8::vec2*, Tmpl8::Sprite* explosion);
	Spawner(Tmpl8::Sprite* explosion);
	virtual ~Spawner();
	void AddExplosionToPool(ExplosionBullet* entity);
	void CreateMoreExplosions();
	void SpawnExplosions(Tmpl8::vec2 pos);
	Tmpl8::vec2 GetDirDeviation();

protected:
	Tmpl8::vec2* pos;
	RandomNumbers randomNumbers;
	//to update
	vector<Entity*> updateObjects;
	pool<ExplosionBullet*> poolOfExplosions;
	//assets 
	Tmpl8::Sprite* explosionSprite;

	float deviationMultiplier = 1.5f;

	//consts
	const float OFFSET = 20.0f;
	const float MIN_DEVIATION = -.1f;
	const float MAX_DEVIATION = .1f;
private:

};

