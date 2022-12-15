#include "EnemyHoarder.h"

#include "game.h"

using namespace Tmpl8;
EnemyHoarder::EnemyHoarder(const PosDir posDir, Sprite* _sprite, EnemyWaveSpawner* _spawner) :
	Enemy(posDir.pos, _sprite, _spawner),
	MAX_DISTANCE_SQUARED_TO_PLAYER(100.0f + _spawner->getMaxPlayerDistanceSquared()),
	rVar(RotationVar(360 / (static_cast<const float>(_sprite->Frames() - 1)), 90.0f, static_cast<const float>(_sprite->GetHeight())))

{
	enemyType = Hoarder;
	enemyCollider = Collider(COL_MIN, COL_MAX, &pos);
	mover.Init(&pos, &dir, &enemyCollider, std::bind(&EnemyHoarder::Reflect, this), SPEED);

	attack = Timer(std::bind(&EnemyHoarder::AtackPlayer, this), TIME_TO_ATTACK, true);
	rotate = Timer();
	rot.Init(&pos, &dir, &rVar, &frame, &mover);

	InitEnemy(mover);
}


void EnemyHoarder::Update(const float deltaTime)
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
	sprite->Draw(screen, static_cast<int>(pos.x - rVar.SPRITE_OFFSET / 2), static_cast<int>(pos.y - rVar.SPRITE_OFFSET / 2));
#ifdef _DEBUG
	screen->Box(static_cast<int>(pos.x + enemyCollider.min.x), static_cast<int>(pos.y + enemyCollider.min.y), static_cast<int>(pos.x + enemyCollider.max.x), static_cast<int>(pos.y + enemyCollider.max.y), 0xffff);


#endif
}



void EnemyHoarder::Init(const PosDir posDir)
{

	SetActive(true);
	pos = posDir.pos;
	dir = posDir.dir;
	hp = static_cast<int>(maxHp);
	mover.SetSpeed(SPEED + randomNumbers.RandomBetweenFloats(MIN_SPEED, MAX_SPEED));
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
	Enemy::Reflect(mover, rot, enemyCollider);

}

void EnemyHoarder::AtackPlayer()
{
	if (InRangeToAtack) {
		Game::Get().PlaySound(SoundID::enemyMeleeAtack);
		spawner->PlayerTakesDamage(this);
		attack.ResetVar();
	}
}

void EnemyHoarder::Die()
{
	Game::Get().PlaySound(SoundID::enemyDeath);

	ResetEnemy();
}

Enemy* EnemyHoarder::clone()
{
	Enemy* enem = new EnemyHoarder(PosDir{ pos,dir }, sprite, spawner);
	SetJsonValues(enem);
	return enem;
}
