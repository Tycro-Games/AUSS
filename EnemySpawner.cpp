#include "EnemySpawner.h"
#include "game.h"

#include "Enemy.h"
using namespace Tmpl8;
using namespace std;
EnemySpawner::EnemySpawner(Tmpl8::vec2& _pos, EnemyWaveSpawner* enemyWave, const Sprite& explosion) :
	Spawner(explosion),
	enemyWave(enemyWave),
	pos(_pos),
	move(new MoveInstance(&pos))
{
	Game::Get().AddMoveable(move);
	timer.Init(this, timeToSpawn);
	timer.isUpdateable = false;
}

EnemySpawner::~EnemySpawner()
{
	delete move;
}


void EnemySpawner::Update(float deltaTime)
{
	if (timer.isUpdateable)
		timer.Update(deltaTime);


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
	timer.Init(this, timeToSpawn);
}
const vec2& EnemySpawner::GetSpawnerPos() const
{
	return pos;
}
//called by timer
void EnemySpawner::Call()
{
	//calls the wave spawner
	Enemy* enemy = enemyWave->SpawnEnemy(pos, enemyToSpawn);
	Tmpl8::vec2 randomDir = GetDirDeviation();
	enemy->Init(PosDir(pos, randomDir));
	//game wiring
	Game::Get().AddCollider(enemy->getColl());
	Game::Get().AddMoveable(enemy->getMoveable());


}
