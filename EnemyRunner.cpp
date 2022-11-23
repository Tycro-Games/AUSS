#include "EnemyRunner.h"

EnemyRunner::EnemyRunner(PosDir posDir, Tmpl8::Sprite* sprite, EnemyWaveSpawner* spawner)
	:Enemy(posDir.pos, sprite, spawner)
{
	enemyType = Runner;
	enemyCollider = Collider(COL_MIN, COL_MAX, &pos);

	rotate = Timer();

	mover.Init(&pos, &dir, &enemyCollider, this);
	rot.Init(&pos, &dir, &rVar, &frame, &mover);

	InitEnemy(mover);
	Init(posDir);
}



void EnemyRunner::Render(Tmpl8::Surface* screen)
{
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x), static_cast<int>(pos.y));
}

void EnemyRunner::Update(float deltaTime)
{
	if (!getUpdateable())
		return;
	rotate.Update(deltaTime);

	CheckForProjectileCollisions();

	mover.Update(deltaTime);
	if (InRangeToAtackPlayerSquared(100)) {
		spawner->PlayerTakesDamage(this);
		Die();
	}
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
	rotate.Init(this, .5f);

	hp = maxHp;
}

void EnemyRunner::ResetEnemy()
{
	spawner->AddEnemyToPool(this, true);
	spawner->SpawnExplosions(pos);
}

void EnemyRunner::Call()
{
}
