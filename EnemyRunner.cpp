#include "EnemyRunner.h"

EnemyRunner::EnemyRunner(PosDir posDir, Tmpl8::Sprite* sprite, EnemyWaveSpawner* spawner)
	:Enemy(posDir.pos, sprite, spawner)
{
	enemyType = Runner;
}

EnemyRunner::~EnemyRunner()
{
}

void EnemyRunner::Render(Tmpl8::Surface* screen)
{
	sprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
}

void EnemyRunner::Update(float deltaTime)
{
}

void EnemyRunner::Die()
{
	ResetEnemy();
}

Enemy* EnemyRunner::clone()
{
	return new EnemyRunner(PosDir(pos, dir), sprite, spawner);
}

void EnemyRunner::Init(PosDir posDir)
{
	SetActive(true);
	pos = posDir.pos;
	dir = posDir.dir;
	hp = 100;
}

void EnemyRunner::ResetEnemy()
{
	spawner->AddEnemyToPool(this, true);
	spawner->SpawnExplosions(pos);
}
