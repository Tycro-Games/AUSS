#include "EnemySpawner.h"
#include "game.h"


EnemySpawner::EnemySpawner(Tmpl8::vec2* pos, EnemyWaveSpawner* enemyWave, Tmpl8::Sprite* explosion) :
	Spawner(pos, explosion),
	enemyWave(enemyWave)
{
	timer = new Timer(this, timeToSpawn);


}

EnemySpawner::~EnemySpawner()
{
	delete timer;

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
bool EnemySpawner::IsEnemy(Collider* col)
{
	return enemyWave->IsEnemy(col);
}
void EnemySpawner::Render(Tmpl8::Surface* screen)
{
	//render a sprite maybe
}
void EnemySpawner::PlayerTakesDamage(Enemy* enemy)
{
	enemyWave->PlayerTakesDamage(enemy);
}
void EnemySpawner::ResetTimer(float timeToSpawn)
{
	timer->Init(this, timeToSpawn);
}
//called by timer
void EnemySpawner::Call()
{
	//calls the wave spawner
	Enemy* enemy = enemyWave->SpawnEnemy(*pos, enemyToSpawn);
	Tmpl8::vec2 randomDir = GetDirDeviation();
	enemy->Init(PosDir(*pos, randomDir));
	//game wiring
	Tmpl8::Game::AddCollider(enemy->getColl());
	Tmpl8::Game::AddMoveable(enemy->getMoveable());


}
