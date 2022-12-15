#include "EnemyShielder.h"
#include "game.h"
using namespace Tmpl8;

EnemyShielder::EnemyShielder(const PosDir posDir, Sprite* _sprite, EnemyWaveSpawner* _spawner) :
	Enemy(posDir.pos, _sprite, _spawner),
	MAX_DISTANCE_SQUARED_TO_PLAYER(2025.0f + _spawner->getMaxPlayerDistanceSquared()),//the square of 45
	rVar(RotationVar(360 / (static_cast<const float>(_sprite->Frames() - 1)), 90.0f,
		static_cast<const float>(_sprite->GetHeight())))
{
	enemyType = Shielder;
	enemyCollider = Collider(COL_MIN, COL_MAX, &pos);
	mover.Init(&pos, &dir, &enemyCollider, std::bind(&EnemyShielder::Reflect, this), SPEED);

	rot.Init(&pos, &shieldDir, &rVar, &frame, &mover);

	InitEnemy(mover);
}

void EnemyShielder::Update(const float deltaTime)
{
	if (!getUpdateable())
		return;

	rotateTimer.Update(deltaTime);
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
	inRangeToAtack_ = InRangeToAtackPlayerSquared(MAX_DISTANCE_SQUARED_TO_PLAYER);
	if (inRangeToAtack_) {
		attackTimer.Update(deltaTime);
	}
	shieldLine.UpdateLine(pos + shieldDir * LINE_OFFSET, MathFunctions::GetDirInDegreesPositive(shieldDir), LINE_SIZE);
	shieldLine.CheckCollisionProjectiles();
}
void EnemyShielder::SpawnEnemies()
{
	//call enemy spawn enemies
	angleToSpawn = MathFunctions::GetDirInDegreesPositive(shieldDir);
	Game::Get().PlaySound(SoundID::enemyShoot);
	SpawnEnemy(1, angleToSpawn, Hoarder, STEP_ANGLE);
	SpawnEnemy(1, angleToSpawn, Runner, STEP_ANGLE);
	SpawnEnemy(1, angleToSpawn, Runner, STEP_ANGLE);
	SpawnEnemy(1, angleToSpawn, Runner, STEP_ANGLE);


}
void EnemyShielder::Reflect()
{
	Enemy::Reflect(mover, rot, enemyCollider);


}
void EnemyShielder::AtackPlayer()
{
	if (inRangeToAtack_) {
		Game::Get().PlaySound(SoundID::enemyMeleeAtack);
		spawner->PlayerTakesDamage(this);
		attackTimer.ResetVar();
	}
}

void EnemyShielder::Render(Surface* screen)
{
	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2), static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2));
#ifdef _DEBUG
	screen->Box(static_cast<int>(pos.x + enemyCollider.min.x), static_cast<int>(pos.y + enemyCollider.min.y),
		static_cast<int>(pos.x + enemyCollider.max.x), static_cast<int>(pos.y + enemyCollider.max.y), 0xFF00FF);

#endif
	//float angle = MathFunctions::GetDirInDegreesPositive(dir);


	shieldLine.Render(screen);
}

void EnemyShielder::Die()
{
	Game::Get().PlaySound(SoundID::enemyDeath);

	ResetEnemy();
}

Enemy* EnemyShielder::clone()
{
	Enemy* enem = new EnemyShielder(PosDir{ pos,dir }, sprite, spawner);
	SetJsonValues(enem);
	return enem;
}

void EnemyShielder::Init(const PosDir posDir)
{
	SetActive(true);
	pos = posDir.pos;
	dir = posDir.dir;
	hp = static_cast<int> (maxHp);


	mover.SetSpeed(SPEED + randomNumbers.RandomBetweenFloats(MIN_SPEED, MAX_SPEED));

	rotateTimer.Init(std::bind(&EnemyRotator::RotateToPlayer, &rot), randomNumbers.RandomBetweenFloats(MIN_TIME_ROTATION, MAX_TIME_ROTATION), true);
	timerToStop.Init(std::bind(&EnemyShielder::StartMovement, this), STOP_INTERVAL);
	timerToMove.Init(std::bind(&EnemyShielder::StopMovement, this), MOVE_INTERVAL);
	timerToSpawn.Init(std::bind(&EnemyShielder::SpawnEnemies, this), SPAWN_INTERVAL, true);
	attackTimer.Init(std::bind(&EnemyShielder::AtackPlayer, this), TIME_TO_ATTACK, true);

	rot.RotateToPlayer();
}
void EnemyShielder::StartMovement()
{
	canMove = true;

	const vec2 toCenter = (vec2{ ScreenWidth / 2.0f,ScreenHeight / 2.0f } - pos);

	dir = (toCenter + MathFunctions::GetRandomVec2(MIN_DEVIATION, MAX_DEVIATION)).normalized();
	timerToMove.ResetVar();
}
void EnemyShielder::StopMovement()
{
	canMove = false;
	timerToStop.ResetVar();
}
void EnemyShielder::ResetEnemy()
{
	spawner->AddEnemyToPool(this, true);
	spawner->SpawnExplosions(pos);
}
