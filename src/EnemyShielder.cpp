#include "EnemyShielder.h"
#include "game.h"
using namespace Tmpl8;

EnemyShielder::EnemyShielder(const PosDir posDir, Sprite* _sprite, EnemyWaveSpawner* _spawner) :
	Enemy(posDir.pos, _sprite, _spawner),
	MAX_DISTANCE_SQUARED_TO_PLAYER(100.0f + _spawner->getMaxPlayerDistanceSquared()),
	rVar(RotationVar(360 / (static_cast<const float>(_sprite->Frames() - 1)), 90.0f,
		static_cast<const float>(_sprite->GetHeight())))
{
	enemyType = Shielder;
	enemyCollider = Collider(COL_MIN, COL_MAX, &pos);
	mover.Init(&pos, &dir, &enemyCollider, std::bind(&EnemyShielder::Reflect, this), SPEED);

	attackTimer = Timer(std::bind(&EnemyShielder::AtackPlayer, this), TIME_TO_ATTACK, true);
	spawnTimer = Timer();
	rotateTimer = Timer();//random
	rot.Init(&pos, &dir, &rVar, &frame, &mover);

	InitEnemy(mover);
}

void EnemyShielder::Update(const float deltaTime)
{
	if (!getUpdateable())
		return;

	rotateTimer.Update(deltaTime);
	spawnTimer.Update(deltaTime);
	CheckForProjectileCollisions();

	mover.Update(deltaTime);
	inRangeToAtack_ = InRangeToAtackPlayerSquared(MAX_DISTANCE_SQUARED_TO_PLAYER);
	if (inRangeToAtack_) {
		attackTimer.Update(deltaTime);
	}
	shieldLine.UpdateLine(pos + dir * LINE_OFFSET, MathFunctions::GetDirInDegreesPositive(dir), LINE_SIZE);
	shieldLine.CheckCollisionProjectiles();
}
void EnemyShielder::SpawnEnemies()
{
	//call enemy spawn enemies
	angleToSpawn = MathFunctions::GetDirInDegreesPositive(dir);
	Game::Get().PlaySound(SoundID::enemyShoot);
	SpawnEnemy(1, angleToSpawn, Hoarder, STEP_ANGLE);
	SpawnEnemy(1, angleToSpawn, Runner, STEP_ANGLE);
	SpawnEnemy(1, angleToSpawn, Runner, STEP_ANGLE);
	SpawnEnemy(1, angleToSpawn, Runner, STEP_ANGLE);


}
void EnemyShielder::Reflect()
{
	//reflect on obstacle
	if (mover.colToReflectFrom != nullptr) {
		const Collider c = *mover.colToReflectFrom;


		rot.Reflect(Collider::GetNormal(c, enemyCollider));

		mover.colToReflectFrom = nullptr;
	}
	//out of bounds
	else
		rot.Reflect(Collider::GetNormalEdgeScreen(mover.nextP, *mover.getColl()));


}
void EnemyShielder::AtackPlayer()
{
	if (inRangeToAtack_) {
		spawner->PlayerTakesDamage(this);
		attackTimer.ResetVar();
	}
}

void EnemyShielder::Render(Surface* screen)
{
	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2)), static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2));
#ifdef _DEBUG
	screen->Box(static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2),
		static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2),
		static_cast<int>(pos.x + rVar.SPRITE_OFFSET / 2),
		static_cast<int>(pos.y + rVar.SPRITE_OFFSET / 2), 0xff00ff);
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


	mover.SetSpeed(SPEED + randomNumbers.RandomBetweenFloats(-30, 100));
	rotateTimer.Init(std::bind(&EnemyRotator::RotateToPlayer, &rot), randomNumbers.RandomBetweenFloats(0.04f, 0.1f), true);
	spawnTimer.Init(std::bind(&EnemyShielder::SpawnEnemies, this), SPAWN_INTERVAL, true);


	rot.RotateToPlayer();
}

void EnemyShielder::ResetEnemy()
{
	spawner->AddEnemyToPool(this, true);
	spawner->SpawnExplosions(pos);
}
