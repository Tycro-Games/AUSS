#include "EnemySpawner.h"
#include "game.h"

#include "Enemy.h"
using namespace Tmpl8;
EnemySpawner::EnemySpawner(Tmpl8::vec2* pos, EnemyWaveSpawner* enemyWave, Tmpl8::Sprite* explosion) :
	Spawner(pos, explosion),
	enemyWave(enemyWave),
	move(new MoveInstance(this->pos))
{
	Game::Get().AddMoveable(move);
	timer = new Timer(this, timeToSpawn);
	timer->isUpdateable = false;
}

EnemySpawner::~EnemySpawner()
{
	delete timer;
	delete move;
	//position is owned by enemy spawner
	delete pos;
}


void EnemySpawner::Update(float deltaTime)
{
	if (timer->isUpdateable)
		timer->Update(deltaTime);


}

Tmpl8::vec2 EnemySpawner::GetPlayerPos()
{
	return enemyWave->GetPlayerPos();
}
void EnemySpawner::SetEnemy(EnemyTypes enemy)
{
	enemyToSpawn = enemy;
}

void EnemySpawner::Render(Tmpl8::Surface* screen)
{
	//render a sprite maybe
}

void EnemySpawner::ResetTimer(float timeToSpawn)
{
	timer->Init(this, timeToSpawn);
}
Tmpl8::vec2 EnemySpawner::GetSpawnerPos() const
{
	return *pos;
}
//called by timer
void EnemySpawner::Call()
{
	//calls the wave spawner
	Enemy* enemy = enemyWave->SpawnEnemy(*pos, enemyToSpawn);
	Tmpl8::vec2 randomDir = GetDirDeviation();
	enemy->Init(PosDir(*pos, randomDir));
	//game wiring
	Game::Get().AddCollider(enemy->getColl());
	Game::Get().AddMoveable(enemy->getMoveable());


}
