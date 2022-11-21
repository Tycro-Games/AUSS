#pragma once
#include "Being.h"

#include "MoveToADirection.h"
#include "PosDir.h"
#include "Wave.h"
#include "EnemyWaveSpawner.h"

#include <filesystem>
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
	Collider* getColl();
	Moveable* getMoveable() const;
	unsigned int getDg() const;
	unsigned int getHp() const;
	unsigned int getScore() const;
	unsigned int getWeight() const;
	EnemyTypes GetEnemyType() const;

protected:
	void SetColToEnemyFlag();
	void Enemy::SetJsonValues(Enemy* enem);
	EnemyTypes enemyType;
	virtual void ResetEnemy() = 0;
	EnemyWaveSpawner* spawner;
	Moveable* move;//needs to be set by children of the enemy
	Collider enemyCollider;
	Tmpl8::vec2 dir;

	unsigned int dg;
	unsigned int maxHp;
	unsigned int weight;
	unsigned int score;
};
//inlined functions
inline void Enemy::SetColToEnemyFlag() {
	enemyCollider.type = Collider::Type::Enemy;
}

inline void Enemy::setDg(unsigned int Dg)
{
	dg = Dg;
}

inline void Enemy::setHp(unsigned int Hp)
{
	maxHp = Hp;
}

inline void Enemy::setScore(unsigned int Score)
{
	score = Score;
}

inline void Enemy::setWeight(unsigned int Weight)
{
	weight = Weight;
}

inline Collider* Enemy::getColl() {
	return &enemyCollider;
}

inline Moveable* Enemy::getMoveable()const {
	return move;
}

inline unsigned int Enemy::getDg() const {
	return dg;
}

inline unsigned int Enemy::getHp() const
{
	return maxHp;
}

inline unsigned int Enemy::getScore() const {
	return score;
}

inline unsigned int Enemy::getWeight() const
{
	return weight;
}

inline EnemyTypes Enemy::GetEnemyType() const {
	return enemyType;
}

