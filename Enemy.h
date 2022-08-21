#pragma once
#include "Entity.h"


#include "MoveToADirection.h"
#include "EnemySpawner.h"
#include "PosDir.h"

class EnemySpawner;
class Enemy : public Entity, public Callable
{
public:

	Enemy(Tmpl8::vec2*, Tmpl8::Sprite* sprite, EnemySpawner* spawner);
	virtual ~Enemy();
	virtual void Init(PosDir) = 0;
	Collider* getColl() const {
		return col;
	}

protected:
	EnemySpawner* spawner;
	Collider* col;


};


