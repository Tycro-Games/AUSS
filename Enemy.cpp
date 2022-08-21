#include "Enemy.h"


Enemy::Enemy(Tmpl8::vec2* pos, Tmpl8::Sprite* sprite, EnemySpawner* spawner) :
	Entity(sprite, pos),
	spawner(spawner),
	col()
{
}

Enemy::~Enemy()
{
	delete col;
}



