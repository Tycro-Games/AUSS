#pragma once
#include "Being.h"

#include "MoveToADirection.h"
#include "PosDir.h"
#include "Wave.h"

#include "EnemyWaveSpawner.h"
//based on https://gameprogrammingpatterns.com/prototype.html
class Enemy : public Being
{
public:
	Enemy(Tmpl8::vec2, Tmpl8::Sprite*, EnemyWaveSpawner*);
	virtual ~Enemy();
	virtual Enemy* clone() = 0;
	virtual void Init(PosDir) = 0;
	void setDg(unsigned int);
	void setHp(unsigned int);
	void setScore(unsigned int);
	void setWeight(unsigned int);
	//get linker errors unless these functions are declared in the header (from enemyWaveSpawner)
	Collider* getColl() const;
	Moveable* getMoveable() const;
	unsigned int getDg() const;
	unsigned int getHp() const;
	unsigned int getScore() const;
	unsigned int getWeight() const;
	EnemyTypes GetEnemyType() const;

protected:
	void Enemy::SetJsonValues(Enemy* enem);
	EnemyTypes enemyType;
	virtual void ResetEnemy() = 0;
	EnemyWaveSpawner* spawner;
	Moveable* move;
	Collider* col;
	Tmpl8::vec2 dir;

	unsigned int dg;
	unsigned int maxHp;
	unsigned int weight;
	unsigned int score;
};


