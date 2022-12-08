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
	/// <summary>
	/// Spawns a runner
	/// </summary>
	/// <param name="sign"></param>
	/// <param name="degreesToSpawn"></param>
	/// <param name="stepDegrees">how many degrees will the degreesToSpawn will be modified</param>

	/// <summary>
	/// 
	/// </summary>
	/// <param name="sign">a -1 or +1 that dictates the direction in the trigonometric </param>
	/// <param name="degreesToSpawn">degrees that make up the vec2</param>
	/// <param name="enemy"></param>
	/// <param name="stepDegrees"></param>
	void SpawnEnemy(const float sign, float& degreesToSpawn, EnemyTypes enemy, const float stepDegrees = 45.0f);



	void setDg(unsigned int);
	void setHp(unsigned int);
	void setScore(unsigned int);
	void setWeight(unsigned int);
	void setDgToTake(unsigned int);
	Collider* getColl();
	Moveable* getMoveable() const;
	unsigned int getDg() const;
	unsigned int getMaxHp() const;
	unsigned int getScore() const;
	unsigned int getWeight() const;
	unsigned int getDgToTake() const;
	EnemyTypes GetEnemyType() const;

protected:
	void CheckForProjectileCollisions();
	/// <summary>
	/// range needs to be squaread
	/// </summary>
	/// <param name="range"></param>
	/// <returns></returns>
	bool InRangeToAtackPlayerSquared(float range);
	void InitEnemy(Moveable& _move);
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
	unsigned int dgToTake;

private:
};
//inlined functions


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

inline void Enemy::setDgToTake(unsigned int dgTo)
{
	dgToTake = dgTo;
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

inline unsigned int Enemy::getMaxHp() const
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

inline unsigned int Enemy::getDgToTake() const
{
	return dgToTake;
}

inline EnemyTypes Enemy::GetEnemyType() const {
	return enemyType;
}

