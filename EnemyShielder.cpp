#include "EnemyShielder.h"

EnemyShielder::EnemyShielder(PosDir posDir, Tmpl8::Sprite* sprite, EnemyWaveSpawner* _spawner) :
	Enemy(posDir.pos, sprite, _spawner),
	rVar(RotationVar(360 / (static_cast<const float>(sprite->Frames() - 1)), 90.0f, static_cast<const float>(sprite->GetHeight()))),
	MAX_DISTANCE_SQUARED_TO_PLAYER(100.0f + _spawner->getMaxPlayerDistanceSquared())

{
	enemyType = Shielder;
	enemyCollider = Collider(COL_MIN, COL_MAX, &pos);
	mover.Init(&pos, &dir, &enemyCollider, std::bind(&EnemyShielder::Reflect, this), SPEED);

	attackTimer = Timer(std::bind(&EnemyShielder::AtackPlayer, this), TIME_TO_ATTACK, true);
	spawnTimer = Timer();
	rotateTimer = Timer();//random
	rot.Init(&pos, &dir, &rVar, &frame, &mover);

	InitEnemy(mover);
	Init(posDir);
}

void EnemyShielder::Update(float deltaTime)
{
	if (!getUpdateable())
		return;

	rotateTimer.Update(deltaTime);
	CheckForProjectileCollisions();

	mover.Update(deltaTime);
	InRangeToAtack = InRangeToAtackPlayerSquared(MAX_DISTANCE_SQUARED_TO_PLAYER);
	if (InRangeToAtack) {
		attackTimer.Update(deltaTime);
	}
}
void EnemyShielder::SpawnEnemies()
{
	//call enemy spawn enemies
}
void EnemyShielder::Reflect()
{
	//reflect on obstacle
	if (mover.colToReflectFrom != nullptr) {
		Collider c = *mover.colToReflectFrom;


		rot.Reflect(Collider::GetNormal(c, enemyCollider));

		mover.colToReflectFrom = nullptr;
	}
	//out of bounds
	else
		rot.Reflect(Collider::GetNormalEdgeScreen(mover.nextP, *mover.getColl()));


}
void EnemyShielder::AtackPlayer()
{
	if (InRangeToAtack) {
		spawner->PlayerTakesDamage(this);
		attackTimer.ResetVar();
	}
}

void EnemyShielder::Render(Tmpl8::Surface* screen)
{
	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2)), static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2));
	screen->Box(static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2),
		static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2),
		static_cast<int>(pos.x + rVar.SPRITE_OFFSET / 2),
		static_cast<int>(pos.y + rVar.SPRITE_OFFSET / 2), 0xff00ff);
}

void EnemyShielder::Die()
{
	ResetEnemy();
}

Enemy* EnemyShielder::clone()
{
	Enemy* enem = new EnemyShielder(PosDir{ pos,dir }, sprite, spawner);
	SetJsonValues(enem);
	return enem;
}

void EnemyShielder::Init(PosDir posDir)
{
	SetActive(true);
	pos = posDir.pos;
	dir = posDir.dir;
	hp = maxHp;


	mover.SetSpeed(SPEED + randomNumbers.RandomBetweenFloats(-30, 100));
	rotateTimer.Init(std::bind(&EnemyRotator::RotateToPlayer, &rot), randomNumbers.RandomBetweenFloats(0.1f, 0.9f), true);
	spawnTimer.Init(std::bind(&EnemyShielder::SpawnEnemies, this), SPAWN_INTERVAL, true);


	rot.RotateToPlayer();
}

void EnemyShielder::ResetEnemy()
{
	spawner->AddEnemyToPool(this, true);
	spawner->SpawnExplosions(pos);
}
