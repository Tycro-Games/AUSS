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



