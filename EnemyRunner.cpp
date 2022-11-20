#include "EnemyRunner.h"

EnemyRunner::EnemyRunner(PosDir posDir, Tmpl8::Sprite* sprite, EnemyWaveSpawner* spawner)
	:Enemy(posDir.pos, sprite, spawner)
{
	enemyType = Runner;
	enemyCollider = Collider(0, 0, &pos);
	mover = new MoveInstance(&this->pos);
	move = mover;
}

EnemyRunner::~EnemyRunner()
{
	delete mover;
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
	Enemy* enem = new EnemyRunner(PosDir(pos, dir), sprite, spawner);
	SetJsonValues(enem);
	return enem;
}



void EnemyRunner::Init(PosDir posDir)
{
	SetActive(true);
	pos = posDir.pos;
	dir = posDir.dir;
	hp = maxHp;
}

void EnemyRunner::ResetEnemy()
{
	spawner->AddEnemyToPool(this, true);
	spawner->SpawnExplosions(pos);
}
