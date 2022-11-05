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
	Moveable* getMoveable() const {
		return move;
	}
	int getDg() {
		return dg;
	}
protected:
	virtual void ResetEnemy() = 0;

	EnemySpawner* spawner;
	Moveable* move;
	Collider* col;
	int dg;
	unsigned int score = 0;
};


