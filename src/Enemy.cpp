#include "Enemy.h"
#include "game.h"
#include "Physics.h"

using namespace Tmpl8;
using namespace std;


Enemy::Enemy(const vec2 _pos, Sprite* _sprite, EnemyWaveSpawner* spawner) :
	Being(_sprite, _pos),
	spawner(spawner),
	dg()
{
	enemyType = EnemyTypes::NUMBER_OF_ENEMIES;
	setDg(0);
	setHp(0);
	setScore(0);
	setWeight(0);
	setDgToTake(0);
}

Enemy::~Enemy()
{
	sprite = nullptr; //this sprite is deleted by the spawner
}

void Enemy::SpawnEnemy(const float sign, float& degreesToSpawn, const EnemyTypes enemy, const float stepDegrees) const
{
	const vec2 direction = (MathFunctions::GetVec2FromRadians(degreesToSpawn * PI / 180 * sign)).normalized();
	spawner->SpawnEnemy(PosDir{
							pos,
							direction
		},
		enemy);
	degreesToSpawn = fmodf(degreesToSpawn + stepDegrees * sign, 360);
}


void Enemy::Reflect(MoveToADirection& mover, Rotator& rot, const Collider& enemyCollider)
{
	if (Physics::InGameScreen(*enemyCollider.pos))
		Game::Get().PlaySound(SoundID::projectileExplosion);

	if (mover.colToReflectFrom != nullptr)
	{
		const Collider c = *mover.colToReflectFrom;


		rot.Reflect(Physics::GetNormal(c, enemyCollider));

		mover.colToReflectFrom = nullptr;
	}
	//out of bounds
	else
	{
		rot.Reflect(Physics::GetNormalEdgeScreen(mover.nextP, *mover.getColl()));
	}
}

void Enemy::SetJsonValues(Enemy* _enemy) const
{
	_enemy->setDg(dg);
	_enemy->setHp(maxHp);
	_enemy->setScore(score);
	_enemy->setWeight(weight);
	_enemy->setDgToTake(dgToTake);
}

void Enemy::CheckForProjectileCollisions()
{
	//marked by collision
	if (enemyCollider.toDeactivate)
	{
		Game::Get().PlaySound(SoundID::enemyHit);
		TakeDamage(dgToTake);
		enemyCollider.toDeactivate = false;
	}
}

bool Enemy::InRangeToAttackPlayerSquared(const float range) const
{
	const float dist = MathFunctions::GetDistanceSqr(pos, Game::Get().getPlayer().GetPos());
	if (dist < range)
	{
		//in range to attack player
		return true;
	}
	return false;
}

void Enemy::InitEnemy(Moveable& _move)
{
	enemyCollider.type = Collider::Type::enemy;
	move = &_move;
}
