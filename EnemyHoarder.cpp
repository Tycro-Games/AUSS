#include "EnemyHoarder.h"
#include "MathFunctions.h"

#include "game.h"
using namespace Tmpl8;
EnemyHoarder::EnemyHoarder(PosDir posDir, Sprite* sprite, EnemyWaveSpawner* _spawner) :
	Enemy(posDir.pos, sprite, _spawner)

{
	enemyType = Hoarder;
	enemyCollider = Collider(COL_MIN, COL_MAX, &pos);
	SetColToEnemyFlag();
	mover.Init(&pos, &dir, &enemyCollider, this, SPEED);
	//as a getter for the base class
	move = &mover;

	attack = Timer(this, TIME_TO_ATTACK, true);
	rotate = Timer();
	rot.Init(&pos, &dir, &rVar, &frame, &mover);

	Init(posDir);
}



EnemyHoarder::~EnemyHoarder()
{

}

void EnemyHoarder::Update(float deltaTime)
{
	if (!getUpdateable())
		return;

	rotate.Update(deltaTime);
	//marked by collision
	if (enemyCollider.toDeactivate) {
		TakeDamage(DG_TO_TAKE);
		enemyCollider.toDeactivate = false;

	}
	else {
		mover.Update(deltaTime);

		dist = MathFunctions::GetDistanceSqr(pos, Game::Get().getPlayer().GetPos());

		if (dist > MAX_DISTANCE_TO_PLAYER) {
			//not in range
			InRangeToAtack = false;
		}
		else if (dist < MAX_DISTANCE_TO_ATTACK) {
			//in range to atack player
			attack.Update(deltaTime);
			InRangeToAtack = true;
		}
		else
		{
			InRangeToAtack = false;
		}

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
	mover.SetSpeed(SPEED + randomNumbers.RandomBetweenFloats(-30, 100));
	rotate.Init(&rot, randomNumbers.RandomBetweenFloats(0.1f, 0.9f), true);
	rot.Call();
}



void EnemyHoarder::ResetEnemy()
{

	spawner->AddEnemyToPool(this, true);
	spawner->SpawnExplosions(pos);
}

void EnemyHoarder::Call()
{
	//ready to atack and in range
	if (attack.FinishedLoop() && InRangeToAtack) {
		spawner->PlayerTakesDamage(this);
		attack.ResetVar();
		//moves a bit after atacking
		ToMove = true;
	}
	else if (mover.colToReflectFrom != nullptr) {
		Collider c = *mover.colToReflectFrom;


		rot.Reflect(Collider::GetNormal(c, enemyCollider));

		mover.colToReflectFrom = nullptr;
	}
	//out of bounds
	else {
		rot.Reflect(Collider::GetNormalEdgeScreen(mover.nextP, *mover.getColl()));
	}

}

void EnemyHoarder::Die()
{
	ResetEnemy();
}

Enemy* EnemyHoarder::clone()
{
	Enemy* enem = new EnemyHoarder(PosDir(pos, dir), sprite, spawner);
	SetJsonValues(enem);
	return enem;
}
