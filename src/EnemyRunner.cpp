#include "EnemyRunner.h"

#include "AudioID.h"
#include "game.h"
using namespace Tmpl8;
EnemyRunner::EnemyRunner(const PosDir posDir, Sprite* _sprite, EnemyWaveSpawner* _spawner)
	:Enemy(posDir.pos, _sprite, _spawner),
	rVar(RotationVar(360 / (static_cast<const float>(_sprite->Frames() - 1)), 90.0f, static_cast<const float>(_sprite->GetHeight()))),
	MAX_DISTANCE_SQUARED_TO_PLAYER(100.0f + _spawner->getMaxPlayerDistanceSquared())


{
	enemyType = EnemyTypes::Runner;
	enemyCollider = Collider(COL_MIN, COL_MAX, &pos);

	mover.Init(&pos, &dir, &enemyCollider, std::bind(&EnemyRunner::Reflect, this), SPEED);
	rot.Init(&pos, &dir, &rVar, &frame, &mover);

	InitEnemy(mover);
}




void EnemyRunner::Render(Surface* screen)
{
	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x + enemyCollider.min.x), static_cast<int>(pos.y + enemyCollider.min.y));
#ifdef _DEBUG
	screen->Box(static_cast<int>(pos.x + enemyCollider.min.x), static_cast<int>(pos.y + enemyCollider.min.y), static_cast<int>(pos.x + enemyCollider.max.x), static_cast<int>(pos.y + enemyCollider.max.y), 0x00FF00);
#endif

}

void EnemyRunner::Update(const float delta_time)
{
	if (!getUpdateable())
		return;
	deathTimer.Update(delta_time);
	CheckForProjectileCollisions();

	mover.Update(delta_time);
	if (InRangeToAtackPlayerSquared(MAX_DISTANCE_SQUARED_TO_PLAYER)) {
		spawner->PlayerTakesDamage(this);
		Die();
	}
}

void EnemyRunner::Die()
{
	Game::Get().PlaySound(SoundID::enemyDeath);

	ResetEnemy();
}

Enemy* EnemyRunner::clone()
{
	Enemy* enem = new EnemyRunner(PosDir{ pos,dir }, sprite, spawner);
	SetJsonValues(enem);
	return enem;
}



void EnemyRunner::Init(PosDir pos_dir)
{
	SetActive(true);
	pos = pos_dir.pos;
	if (pos_dir.dir.length() > 0)
		dir = pos_dir.dir;
	else {
		dir = MathFunctions::GetRandomVec2(0.1f, 1.0f).normalized();//random direction
	}

	deathTimer.Init(std::bind(&EnemyRunner::Die, this), TIME_ALIVE);
	hp = static_cast<int>(maxHp);
	frame = MathFunctions::RotateToDirectionFrames(rVar, dir);

}

void EnemyRunner::ResetEnemy()
{
	//runners do not give points
	spawner->AddEnemyToPool(this);

	spawner->SpawnExplosions(pos);
}

void EnemyRunner::Reflect()
{
	Enemy::Reflect(mover, rot, enemyCollider);
}
