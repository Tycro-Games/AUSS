#include "EnemyShooter.h"
#include "game.h"
using namespace Tmpl8;
EnemyShooter::EnemyShooter(PosDir posDir, Sprite* _sprite, EnemyWaveSpawner* _spawner) :
	Enemy(posDir.pos, _sprite, _spawner),
	rVar(RotationVar(360 / (static_cast<const float>(sprite->Frames() - 1)), 90.0f, static_cast<const float>(sprite->GetHeight())))

{
	enemyType = Shooter;
	enemyCollider = Collider(COL_MIN, COL_MAX, &pos);

	mover.Init(&pos, &dir, &enemyCollider, std::bind(&EnemyShooter::Reflect, this), 300);

	InitEnemy(mover);
	Init(posDir);
}

void EnemyShooter::Update(float deltaTime)
{
	if (!getUpdateable())
		return;
	CheckForProjectileCollisions();

	if (canMove) {
		mover.Update(deltaTime);
		timerToMove.Update(deltaTime);
	}
	else {
		//not moving, shoot
		timerToStop.Update(deltaTime);
		timerToSpawn.Update(deltaTime);
	}


}

void EnemyShooter::Render(Tmpl8::Surface* screen)
{
	if (!getRenderable())
		return;
	sprite->Draw(screen, static_cast<int>(pos.x + enemyCollider.min.x), static_cast<int>(pos.y + enemyCollider.min.y));
#ifdef _DEBUG
	screen->Box(static_cast<int>(pos.x + enemyCollider.min.x), static_cast<int>(pos.y + enemyCollider.min.y), static_cast<int>(pos.x + enemyCollider.max.x), static_cast<int>(pos.y + enemyCollider.max.y), 0x00FFF0);
#endif


}

void EnemyShooter::Die()
{
	ResetEnemy();
}

Enemy* EnemyShooter::clone()
{
	Enemy* enem = new EnemyShooter(PosDir{ pos,dir }, sprite, spawner);
	SetJsonValues(enem);
	return enem;
}

void EnemyShooter::Init(PosDir posDir)
{
	SetActive(true);
	pos = posDir.pos;
	dir = posDir.dir;

	rot.Init(&pos, &dir, &rVar, &frame, &mover);
	hp = maxHp;
	canMove = false;
	timerToStop.Init(std::bind(&EnemyShooter::StartMovement, this), STOP_INTERVAL);
	timerToMove.Init(std::bind(&EnemyShooter::StopMovement, this), MOVE_INTERVAL);

	timerToSpawn.Init(std::bind(&EnemyShooter::SpawnRunner, this), SPAWN_INTERVAL, true);
}

void EnemyShooter::ResetEnemy()
{
	spawner->AddEnemyToPool(this, true);

	spawner->SpawnExplosions(pos);
}

void EnemyShooter::StartMovement()
{
	canMove = true;

	vec2 toCenter = (vec2{ ScreenWidth / 2,ScreenHeight / 2 } - pos);

	dir = (toCenter + MathFunctions::GetRandomVec2(MIN_DEVIATION, MAX_DEVIATION)).normalized();
	timerToMove.ResetVar();
}

void EnemyShooter::SpawnRunner()
{
	Enemy::SpawnEnemy(randomNumbers.RandomMinusPlusSign(), angleToSpawn, Runner, STEP_ANGLE);
}



void EnemyShooter::StopMovement()
{
	canMove = false;
	timerToStop.ResetVar();
}

void EnemyShooter::Reflect()
{
	//reflect on obstacle
	if (mover.colToReflectFrom != nullptr) {
		Collider c = *mover.colToReflectFrom;
		rot.Reflect(Collider::GetNormal(c, enemyCollider));
		mover.colToReflectFrom = nullptr;
	}
	else //or edge of the screen
		rot.Reflect(Collider::GetNormalEdgeScreen(mover.nextP, *mover.getColl()));

}
