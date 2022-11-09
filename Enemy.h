#pragma once
#include "Being.h"

#include "MoveToADirection.h"
#include "EnemyWaveSpawner.h"
#include "PosDir.h"
//based on https://gameprogrammingpatterns.com/prototype.html
class Enemy : public Being
{
public:
	Enemy(Tmpl8::vec2, Tmpl8::Sprite*, EnemyWaveSpawner*);
	virtual ~Enemy();
	virtual Enemy* clone() = 0;
	virtual void Init(PosDir) = 0;

	Collider* getColl() const {
		return col;
	}
	Moveable* getMoveable() const {
		return move;
	}
	int getDg() const {
		return dg;
	}
	EnemyTypes GetEnemyType() {
		return enemyType;
	}
protected:
	EnemyTypes enemyType;
	virtual void ResetEnemy() = 0;
	EnemyWaveSpawner* spawner;
	Moveable* move;
	Collider* col;
	Tmpl8::vec2 dir;
	int dg;
	unsigned int score = 0;
};


