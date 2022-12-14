#include "EnemySpawner.h"
#include "game.h"

#include "Enemy.h"
using namespace Tmpl8;
using namespace std;
EnemySpawner::EnemySpawner(const vec2 _pos, Sprite* explosion) :
	Spawner(explosion),
	pos(_pos)

{
	move.Init(&pos);
	Game::Get().AddMoveable(&move);

}



void EnemySpawner::Update(float deltaTime)
{
	//animation maybe?
}


void EnemySpawner::SetEnemy(const EnemyTypes enemy)
{
	enemyToSpawn = enemy;
}

void EnemySpawner::Render(Surface* screen)
{
	//render a sprite maybe
}


const vec2& EnemySpawner::GetSpawnerPos() const
{
	return pos;
}

