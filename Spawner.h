#pragma once

#include "vector.h"
#include "pool.h"

#include "ExplosionBullet.h"
#include "Entity.h"
#include "Collider.h"
#include "RandomNumbers.h"
class ExplosionBullet;
class Spawner : public Updateable, public Renderable
{
public:
	Spawner(Tmpl8::vec2*, Tmpl8::vec2*, Tmpl8::Sprite* explosion);
	virtual ~Spawner();
	vector<Collider*>& GetActiveColliders();
	void AddExplosionToPool(ExplosionBullet* entity);
	void CreateMoreExplosions();
	void SpawnExplosions(Tmpl8::vec2 pos);
protected:
	Tmpl8::vec2* pos;
	Tmpl8::vec2* dir;
	RandomNumbers randomNumbers;
	//to update
	vector<Entity*> updateObjects;
	pool<ExplosionBullet*> poolOfExplosions;
	vector<Collider*> activeColliders;
	//assets 
	Tmpl8::Sprite* explosionSprite;

	//consts
	const float OFFSET = 20.0f;
private:

};

