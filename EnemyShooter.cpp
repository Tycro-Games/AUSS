#include "EnemyShooter.h"
using namespace Tmpl8;
EnemyShooter::EnemyShooter(PosDir posDir, Sprite* _sprite, EnemyWaveSpawner* _spawner) :
	Enemy(posDir.pos, _sprite, _spawner),
	rVar(RotationVar(360 / (static_cast<const float>(sprite->Frames() - 1)), 90.0f, static_cast<const float>(sprite->GetHeight()))),

	MAX_DISTANCE_SQUARED_TO_PLAYER(100.0f + _spawner->getMaxPlayerDistance())

{
	enemyType = Shooter;
	enemyCollider = Collider(COL_MIN, COL_MAX, &pos);

	mover.Init(&pos, &dir, &enemyCollider, this, 200);

	InitEnemy(mover);
	Init(posDir);
}

void EnemyShooter::Update(float deltaTime)
{
	if (!getUpdateable)
		return;
	if (canMove) {
		mover.Update(deltaTime);
	}
	else {

	}
	moveIntervalsTimer.Update(deltaTime);
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
}

Enemy* EnemyShooter::clone()
{
	return nullptr;
}

void EnemyShooter::Init(PosDir posDir)
{
	SetActive(true);
	pos = posDir.pos;
	dir = vec2{ -randomNumbers.RandomBetweenFloats(0.1f,1.0f),randomNumbers.RandomBetweenFloats(0.1f,1.0f) };
	dir.normalize();
	hp = maxHp;
	moveIntervalsTimer.Init(this, MOVE_INTERVAL, true);
}

void EnemyShooter::ResetEnemy()
{
}

void EnemyShooter::Call()
{
	canMove = !canMove;
	if(canMove)
		dir = vec2{ randomNumbers.RandomBetweenFloats(0.1f,1.0f),randomNumbers.RandomBetweenFloats(0.1f,1.0f) };
}
