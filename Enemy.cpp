#include "Enemy.h"


Enemy::Enemy(Tmpl8::vec2 pos, Tmpl8::Sprite* sprite, EnemyWaveSpawner* spawner) :
	Being(sprite, pos),
	spawner(spawner),
	col(),
	dg()

{
}

Enemy::~Enemy()
{
	delete col;
}

inline Collider* Enemy::getColl() const {
	return col;
}

inline Moveable* Enemy::getMoveable() const {
	return move;
}

inline unsigned int Enemy::getDg() const {
	return dg;
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

