#pragma once

#include "vector.h"
#include "pool.h"

#include "Entity.h"
#include "RandomNumbers.h"

class Spawner : public Updateable, public Renderable
{
public:
	Spawner(Tmpl8::vec2*);
	~Spawner();
protected:
	Tmpl8::vec2* pos;

	RandomNumbers randomNumbers;
	//to update
	vector<Entity*> updateObjects;

private:

};

