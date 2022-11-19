#include "Enemy.h"

using namespace Tmpl8;
using namespace std;


Enemy::Enemy(Tmpl8::vec2 pos, Tmpl8::Sprite* sprite, EnemyWaveSpawner* spawner) :
	Being(sprite, pos),
	spawner(spawner),
	enemyCollider(),
	dg()
{
}
Enemy::~Enemy()
{
	sprite = nullptr;//this sprite is deleted by the spawner
	delete enemyCollider;
}



void Enemy::SetJsonValues(Enemy* enem)
{
	enem->setDg(dg);
	enem->setHp(maxHp);
	enem->setScore(score);
	enem->setWeight(weight);
}

