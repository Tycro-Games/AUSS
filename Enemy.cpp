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

void Enemy::SetJsonValues(Enemy* enem)
{
	enem->setDg(dg);
	enem->setHp(maxHp);
	enem->setScore(score);
	enem->setWeight(weight);
}

