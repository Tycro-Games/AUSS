#include "EnemyHoarder.h"
#include "MathFunctions.h"

using namespace Tmpl8;
EnemyHoarder::EnemyHoarder(PosDir posDir, Sprite* sprite, EnemyWaveSpawner* _spawner) :
	Enemy(posDir.pos, sprite, _spawner),
	rVar(RotationVar(360 / (static_cast<const float>(sprite->Frames() - 1)), 90.0f, static_cast<const float>(sprite->GetHeight()))),
	MAX_DISTANCE_SQUARED_TO_PLAYER(100.0f + _spawner->getMaxPlayerDistanceSquared())

{
	enemyType = Hoarder;
	enemyCollider = Collider(COL_MIN, COL_MAX, &pos);
	mover.Init(&pos, &dir, &enemyCollider, std::bind(&EnemyHoarder::Reflect, this), SPEED);

	attack = Timer(std::bind(&EnemyHoarder::AtackPlayer, this), TIME_TO_ATTACK, true);
	rotate = Timer();
	rot.Init(&pos, &dir, &rVar, &frame, &mover);

	InitEnemy(mover);
	Init(posDir);
}


void EnemyHoarder::Update(float deltaTime)
{
	if (!getUpdateable())
		return;

	rotate.Update(deltaTime);
	CheckForProjectileCollisions();

	mover.Update(deltaTime);
	InRangeToAtack = InRangeToAtackPlayerSquared(MAX_DISTANCE_SQUARED_TO_PLAYER);
	if (InRangeToAtack) {
		attack.Update(deltaTime);
	}
}





void EnemyHoarder::Render(Surface* screen)
{
	if (!getRenderable())
		return;
	sprite->SetFrame(frame);
	sprite->Draw(screen, static_cast<int>(static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2)), static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2));
	screen->Box(static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2),
		static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2),
		static_cast<int>(pos.x + rVar.SPRITE_OFFSET / 2),
		static_cast<int>(pos.y + rVar.SPRITE_OFFSET / 2), 0xffff);

}



void EnemyHoarder::Init(PosDir posDir)
{

	SetActive(true);
	pos = posDir.pos;
	dir = posDir.dir;
	hp = maxHp;
	mover.SetSpeed(SPEED + randomNumbers.RandomBetweenFloats(50.0f, 100.0f));
	rotate.Init(std::bind(&EnemyRotator::RotateToPlayer, &rot), randomNumbers.RandomBetweenFloats(0.1f, 0.9f), true);
	rot.RotateToPlayer();
}



void EnemyHoarder::ResetEnemy()
{

	spawner->AddEnemyToPool(this, true);
	spawner->SpawnExplosions(pos);
}

void EnemyHoarder::Reflect()
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

void EnemyHoarder::AtackPlayer()
{
	if (InRangeToAtack) {
		spawner->PlayerTakesDamage(this);
		attack.ResetVar();
	}
}

void EnemyHoarder::Die()
{
	ResetEnemy();
}

Enemy* EnemyHoarder::clone()
{
	Enemy* enem = new EnemyHoarder(PosDir{ pos,dir }, sprite, spawner);
	SetJsonValues(enem);
	return enem;
}
