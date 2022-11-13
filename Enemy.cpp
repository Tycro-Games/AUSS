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

void Enemy::setDg(unsigned int Dg)
{
	dg = dg;
}

void Enemy::setHp(unsigned int Hp)
{
	maxHp = Hp;
}

void Enemy::setScore(unsigned int Score)
{
	score = Score;
}

void Enemy::setWeight(unsigned int Weight)
{
	weight = Weight;
}

//get linker errors unless these functions are declared in the header (from enemyWaveSpawner)

Collider* Enemy::getColl() const {
	return col;
}

Moveable* Enemy::getMoveable() const {
	return move;
}

unsigned int Enemy::getDg() const {
	return dg;
}

unsigned int Enemy::getHp() const
{
	return maxHp;
}

unsigned int Enemy::getScore() const {
	return score;
}

unsigned int Enemy::getWeight() const
{
	return weight;
}

EnemyTypes Enemy::GetEnemyType() const {
	return enemyType;
}

void Enemy::SetJsonValues(Enemy* enem)
{
	enem->setDg(dg);
	enem->setHp(maxHp);
	enem->setScore(score);
	enem->setWeight(weight);
}

