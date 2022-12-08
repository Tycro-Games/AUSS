#pragma once
#include "Enemy.h"
#include "EnemyRotator.h"
class EnemyShielder : public Enemy
{
public:
	EnemyShielder(PosDir posDir, Tmpl8::Sprite* sprite, EnemyWaveSpawner* _spawner);
	~EnemyShielder() = default;

	void Update(float deltaTime) override;
	void AtackPlayer();
	void Render(Tmpl8::Surface* screen) override;
	void Init(PosDir) override;
	Enemy* clone() override;
private:
	void SpawnEnemies();
	void Reflect();
	void ResetEnemy() override;
	void Die() override;

	bool InRangeToAtack = false;

	//consts
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-10, -10);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(10, 10);
	const float TIME_TO_ATTACK = 0.25f;
	const float SPAWN_INTERVAL = 0.5f;

	const float SPEED = 50.0f;
	const float MAX_DISTANCE_SQUARED_TO_PLAYER;
	//timers
	Timer attackTimer;
	Timer spawnTimer;
	Timer rotateTimer;

	MoveToADirection mover;
	RandomNumbers randomNumbers;

	RotationVar rVar;

	EnemyRotator rot;


};

