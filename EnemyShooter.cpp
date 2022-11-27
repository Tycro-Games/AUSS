#include "EnemyShooter.h"
using namespace Tmpl8;
EnemyShooter::EnemyShooter(PosDir posDir, Sprite* _sprite, EnemyWaveSpawner* _spawner) :
	Enemy(posDir.pos, _sprite, _spawner),
	rVar(RotationVar(360 / (static_cast<const float>(sprite->Frames() - 1)), 90.0f, static_cast<const float>(sprite->GetHeight())))

{
	enemyType = Shooter;
	enemyCollider = Collider(COL_MIN, COL_MAX, &pos);

	mover.Init(&pos, &dir, &enemyCollider, this, 200);

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
		//not moving, shoot or something
		timerToStop.Update(deltaTime);
		timerToSpawn.Update(deltaTime);
	}


}

void EnemyShooter::Render(Tmpl8::Surface* screen)
{
	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x + enemyCollider.min.x), static_cast<int>(pos.y + enemyCollider.min.y));
	screen->Box(static_cast<int>(pos.x + enemyCollider.min.x), static_cast<int>(pos.y + enemyCollider.min.y), static_cast<int>(pos.x + enemyCollider.max.x), static_cast<int>(pos.y + enemyCollider.max.y), 0x00FFF0);



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
	dir = MathFunctions::GetRandomVec2(MIN_DEVIATION, MAX_DEVIATION).normalized();

	rot.Init(&pos, &dir, &rVar, &frame, &mover);
	hp = maxHp;
	canMove = false;
	timerToStop.Init(this, STOP_INTERVAL);
	timerToSpawn.Init(this, SPAWN_INTERVAL, true);
	timerToMove.isFinished = true;
}

void EnemyShooter::ResetEnemy()
{
	spawner->AddEnemyToPool(this, true);

	spawner->SpawnExplosions(pos);
}

void EnemyShooter::Call()
{

	if (!timerToSpawn.FinishedLoop()) { //not triggered by the spawn timer
		canMove = !canMove;
		if (canMove) {

			//nor normalizing the dir will give it more or less speed
			dir = MathFunctions::GetRandomVec2(MIN_DEVIATION, MAX_DEVIATION);
			timerToStop.Init(this, STOP_INTERVAL);

		}
		else {
			timerToMove.Init(this, MOVE_INTERVAL);
		}
		if (mover.colToReflectFrom != nullptr) {
			Collider c = *mover.colToReflectFrom;


			rot.Reflect(Collider::GetNormal(c, enemyCollider));

			mover.colToReflectFrom = nullptr;
		}
		else
			rot.Reflect(Collider::GetNormalEdgeScreen(mover.nextP, *mover.getColl()));

	}
	else {//spawn enemy
		vec2 direction = (MathFunctions::GetVec2FromAngle(angleToSpawn)).normalized();
		spawner->SpawnEnemy(PosDir{
			pos ,
			direction },
			Runner);
		std::cout << direction.x << " " << direction.y << '\n';
		angleToSpawn = fmodf(angleToSpawn + STEP_ANGLE, 360);
	}
}
