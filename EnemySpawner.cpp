#include "EnemySpawner.h"
#include "game.h"

#include "Enemy.h"
using namespace Tmpl8;
using namespace std;
EnemySpawner::EnemySpawner(Tmpl8::vec2& _pos, EnemyWaveSpawner* enemyWave, Sprite* explosion) :
	Spawner(explosion),
	enemyWave(enemyWave),
	pos(_pos)

{
	move.Init(&pos);
	Game::Get().AddMoveable(&move);

}

EnemySpawner::~EnemySpawner()
{
}


void EnemySpawner::Update(float deltaTime)
{
	//animation maybe?
}


void EnemySpawner::SetEnemy(EnemyTypes enemy)
{
	enemyToSpawn = enemy;
}

void EnemySpawner::Render(Tmpl8::Surface* screen)
{
	//render a sprite maybe
}


const vec2& EnemySpawner::GetSpawnerPos() const
{
	return pos;
}

