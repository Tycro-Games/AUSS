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
	if (!getUpdateable())
		return;
	if (canMove) {
		mover.Update(deltaTime);
	}
	else {
		//not moving, shoot or something
	
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
	dir = vec2{ -randomNumbers.RandomBetweenFloats(0.1f,1.0f),randomNumbers.RandomBetweenFloats(0.1f,1.0f) };
	dir.normalize();
	hp = maxHp;
	moveIntervalsTimer.Init(this, MOVE_INTERVAL, true);
}

void EnemyShooter::ResetEnemy()
{
	spawner->AddEnemyToPool(this, true);

	spawner->SpawnExplosions(pos);
}

void EnemyShooter::Call()
{
	canMove = !canMove;
	if (canMove) {
		//random negative or positive
		bool xNegative = randomNumbers.RandomBetweenInts(0, 2) == 1;
		bool yNegative = randomNumbers.RandomBetweenInts(0, 2) == 1;
		std::cout << xNegative << " " << yNegative << '\n';
		//into floats that make the vec2
		float xPos = randomNumbers.RandomBetweenFloats(0.1f, 1.0f);
		if (xNegative)
			xPos *= -1;
		float yPos = randomNumbers.RandomBetweenFloats(0.1f, 1.0f);
		if (yNegative)
			yPos *= -1;
		std::cout << xPos << " " << yPos << '\n';
		dir = vec2{ xPos,yPos }.normalized();
		std::cout << dir.x << " " << dir.y << '\n';

	}
}
