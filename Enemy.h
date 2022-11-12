#pragma once
#include "nlohmann_json/single_include/nlohmann/json.hpp"
#include "Being.h"

#include "MoveToADirection.h"
#include "EnemyWaveSpawner.h"
#include "PosDir.h"

using json = nlohmann::json;
//based on https://gameprogrammingpatterns.com/prototype.html
class Enemy : public Being
{
public:
	Enemy(Tmpl8::vec2, Tmpl8::Sprite*, EnemyWaveSpawner*);
	virtual ~Enemy();
	virtual Enemy* clone() = 0;
	virtual void Init(PosDir) = 0;
	void SetJsonValues() {

	}
	Collider* getColl() const;
	Moveable* getMoveable() const;
	unsigned int getDg() const;
	unsigned int getScore() const;
	unsigned int getWeight() const;
	EnemyTypes GetEnemyType() const;

protected:
	EnemyTypes enemyType;
	virtual void ResetEnemy() = 0;
	EnemyWaveSpawner* spawner;
	Moveable* move;
	Collider* col;
	Tmpl8::vec2 dir;

	unsigned int dg;
	unsigned int weight;
	unsigned int score = 0;
};


