#pragma once
#include "Being.h"


#include "MoveToADirection.h"
#include "EnemySpawner.h"
#include "PosDir.h"

class EnemySpawner;
class Enemy : public Being
{
public:

	Enemy(Tmpl8::vec2, Tmpl8::Sprite* sprite, EnemySpawner* spawner);
	virtual ~Enemy();
	virtual void Init(PosDir) = 0;
	Collider* getColl() const {
		return col;
	}
	int getDg() {
		return dg;
	}
protected:
	EnemySpawner* spawner;
	Collider* col;
	Tmpl8::vec2 offset;
	int dg;

};


