#include "EnemyShielder.h"

EnemyShielder::EnemyShielder(PosDir posDir, Tmpl8::Sprite* sprite, EnemyWaveSpawner* _spawner) :
	Enemy(posDir.pos, sprite, _spawner),
	rVar(RotationVar(360 / (static_cast<const float>(sprite->Frames() - 1)), 90.0f, static_cast<const float>(sprite->GetHeight()))),
	MAX_DISTANCE_SQUARED_TO_PLAYER(100.0f + _spawner->getMaxPlayerDistance())

{
	enemyType = Shielder;
	enemyCollider = Collider(COL_MIN, COL_MAX, &pos);
	mover.Init(&pos, &dir, &enemyCollider, std::bind(&EnemyShielder::Reflect, this), SPEED);

	attack = Timer(std::bind(&EnemyShielder::AtackPlayer, this), TIME_TO_ATTACK, true);
	rotate = Timer();
	rot.Init(&pos, &dir, &rVar, &frame, &mover);

	InitEnemy(mover);
	Init(posDir);
}

void EnemyShielder::Update(float deltaTime)
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
void EnemyShielder::Reflect()
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
void EnemyShielder::AtackPlayer()
{
	if (InRangeToAtack) {
		spawner->PlayerTakesDamage(this);
		attack.ResetVar();
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
	rotate.Init(std::bind(&EnemyRotator::Call, &rot), randomNumbers.RandomBetweenFloats(0.1f, 0.9f), true);
	rot.Call();
}

void EnemyShielder::ResetEnemy()
{
	spawner->AddEnemyToPool(this, true);
	spawner->SpawnExplosions(pos);
}
