#include "Enemy.h"
#include "game.h"

using namespace Tmpl8;
using namespace std;


Enemy::Enemy(Tmpl8::vec2 pos, Tmpl8::Sprite* sprite, EnemyWaveSpawner* spawner) :
	Being(sprite, pos),
	spawner(spawner),
	enemyCollider(),
	dg()
{
	enemyType = NUMBER_OF_ENEMIES;
	setDg(0);
	setHp(0);
	setScore(0);
	setWeight(0);
	setDgToTake(0);
}
Enemy::~Enemy()
{
	sprite = nullptr;//this sprite is deleted by the spawner
}

void Enemy::SpawnEnemy(const float sign, float& degreesToSpawn, EnemyTypes enemy, const float stepDegrees)
{
	vec2 direction = (MathFunctions::GetVec2FromRadians(degreesToSpawn * PI / 180 * sign)).normalized();
	spawner->SpawnEnemy(PosDir{
		pos ,
		direction },
		enemy);
	degreesToSpawn = fmodf(degreesToSpawn + stepDegrees * sign, 360);
}



void Enemy::SetJsonValues(Enemy* enem)
{
	enem->setDg(dg);
	enem->setHp(maxHp);
	enem->setScore(score);
	enem->setWeight(weight);
	enem->setDgToTake(dgToTake);
}

void Enemy::CheckForProjectileCollisions()
{
	//marked by collision
	if (enemyCollider.toDeactivate) {
		TakeDamage(dgToTake);
		enemyCollider.toDeactivate = false;
	}
}

bool Enemy::InRangeToAtackPlayerSquared(float range)
{
	float dist = MathFunctions::GetDistanceSqr(pos, Game::Get().getPlayer().GetPos());

	if (dist < range) {
		//in range to atack player
		return true;
	}

	return false;

}

void Enemy::InitEnemy(Moveable& _move)
{
	enemyCollider.type = Collider::Type::Enemy;
	move = &_move;
}

