#include "EnemyRunner.h"
using namespace Tmpl8;
EnemyRunner::EnemyRunner(PosDir posDir, Sprite* sprite, EnemyWaveSpawner* _spawner)
	:Enemy(posDir.pos, sprite, _spawner),
	rVar(RotationVar(360 / (static_cast<const float>(sprite->Frames() - 1)), 90.0f, static_cast<const float>(sprite->GetHeight()))),
	MAX_DISTANCE_SQUARED_TO_PLAYER(100.0f + _spawner->getMaxPlayerDistance())


{
	enemyType = Runner;
	enemyCollider = Collider(COL_MIN, COL_MAX, &pos);

	mover.Init(&pos, &dir, &enemyCollider, std::bind(&EnemyRunner::Reflect, this), SPEED);
	rot.Init(&pos, &dir, &rVar, &frame, &mover);

	InitEnemy(mover);
	Init(posDir);
}



void EnemyRunner::Render(Surface* screen)
{
	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x + enemyCollider.min.x), static_cast<int>(pos.y + enemyCollider.min.y));
	screen->Box(static_cast<int>(pos.x + enemyCollider.min.x), static_cast<int>(pos.y + enemyCollider.min.y), static_cast<int>(pos.x + enemyCollider.max.x), static_cast<int>(pos.y + enemyCollider.max.y), 0x00FF00);


}

void EnemyRunner::Update(float deltaTime)
{
	if (!getUpdateable())
		return;
	deathTimer.Update(deltaTime);
	CheckForProjectileCollisions();

	mover.Update(deltaTime);
	if (InRangeToAtackPlayerSquared(MAX_DISTANCE_SQUARED_TO_PLAYER)) {
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
	Enemy* enem = new EnemyRunner(PosDir{ pos,dir }, sprite, spawner);
	SetJsonValues(enem);
	return enem;
}



void EnemyRunner::Init(PosDir posDir)
{
	SetActive(true);
	pos = posDir.pos;

	dir = posDir.dir;
	deathTimer.Init(std::bind(&EnemyRunner::Die, this), TIME_ALIVE);
	hp = maxHp;
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
	if (mover.colToReflectFrom != nullptr) {
		Collider c = *mover.colToReflectFrom;


		rot.Reflect(Collider::GetNormal(c, enemyCollider));

		mover.colToReflectFrom = nullptr;
	}
	//out of bounds
	else {
		rot.Reflect(Collider::GetNormalEdgeScreen(mover.nextP, *mover.getColl()));
	}
}
