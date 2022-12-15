#pragma once
#include "Being.h"

#include "PosDir.h"
#include "Wave.h"
#include "EnemyWaveSpawner.h"
#include "Rotator.h"

//based on https://gameprogrammingpatterns.com/prototype.html
class Enemy : public Being
{
public:
	Enemy(Tmpl8::vec2, Tmpl8::Sprite*, EnemyWaveSpawner*);
	~Enemy() override;
	virtual Enemy* clone() = 0;
	virtual void Init(PosDir) = 0;

	/// <summary>
	/// Spawns an enemy around a vec2 made by the unit circle using the degrees and sign
	/// </summary>
	/// <param name="sign">a -1 or +1 that dictates the direction in the trigonometric </param>
	/// <param name="degreesToSpawn">degrees that make up the vec2</param>
	/// <param name="enemy">The type of enemy to spawn</param>
	/// <param name="stepDegrees">how much the degreesToSpawn will change when the method is finished</param>
	void SpawnEnemy(float sign, float& degreesToSpawn, EnemyTypes enemy, float stepDegrees = 45.0f) const;


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
	EnemyTypes getEnemyType() const;

protected:
	static void Reflect(MoveToADirection& mover, Rotator& rot, const Collider& enemyCollider);
	void CheckForProjectileCollisions();

	/// <summary>
	/// range needs to be squared
	/// </summary>
	/// <param name="range"></param>
	/// <returns></returns>
	bool InRangeToAtackPlayerSquared(float range) const;
	void InitEnemy(Moveable& _move);
	void SetJsonValues(Enemy* enem) const;
	EnemyTypes enemyType;
	virtual void ResetEnemy() = 0;
	EnemyWaveSpawner* spawner;
	Moveable* move{};//needs to be set by children of the enemy
	Collider enemyCollider;
	Tmpl8::vec2 dir = { 0 };

	unsigned int dg;
	unsigned int maxHp{};
	unsigned int weight{};
	unsigned int score{};
	unsigned int dgToTake{};

private:
};
//inlined functions


inline void Enemy::setDg(const unsigned int _dg)
{
	dg = _dg;
}

inline void Enemy::setHp(const unsigned int _hp)
{
	maxHp = _hp;
}

inline void Enemy::setScore(const unsigned int _score)
{
	score = _score;
}

inline void Enemy::setWeight(const unsigned int _weight)
{
	weight = _weight;
}

inline void Enemy::setDgToTake(const unsigned int dgTo)
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

inline EnemyTypes Enemy::getEnemyType() const {
	return enemyType;
}

