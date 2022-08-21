#pragma once

#include "vector.h"
#include "pool.h"

#include "Entity.h"
#include "Collider.h"
#include "RandomNumbers.h"

class Spawner : public Updateable, public Renderable
{
public:
	Spawner(Tmpl8::vec2*, Tmpl8::vec2*);
	virtual ~Spawner();
	vector<Collider*>& GetActiveColliders();
protected:
	Tmpl8::vec2* pos;
	Tmpl8::vec2* dir;
	RandomNumbers randomNumbers;
	//to update
	vector<Entity*> updateObjects;
	vector<Collider*> activeColliders;

	//consts
	const float OFFSET = 20.0f;
private:

};

