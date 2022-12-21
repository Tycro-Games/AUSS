#pragma once
#include "Enemy.h"
#include "EnemyRotator.h"
#include "ShieldLine.h"
class EnemyShielder final : public Enemy
{
public:
	EnemyShielder(PosDir posDir, Tmpl8::Sprite* _sprite, EnemyWaveSpawner* _spawner);
	~EnemyShielder() override = default;

	void Update(float deltaTime) override;
	void attackPlayer();
	void Render(Tmpl8::Surface* screen) override;
	void Init(PosDir) override;
	void StartMovement();
	void StopMovement();
	Enemy* clone() override;
private:
	void SpawnEnemies();
	void Reflect();
	void ResetEnemy() override;
	void Die() override;

	bool inRangeToAttack_ = false;
	bool canMove = false;

	//consts
	const Tmpl8::vec2 COL_MIN = Tmpl8::vec2(-33, -33);
	const Tmpl8::vec2 COL_MAX = Tmpl8::vec2(33, 33);
	const float LINE_OFFSET = 47.0f;
	const float LINE_SIZE = 30.0f;
	const float MAX_DISTANCE_SQUARED_TO_PLAYER;
	const float STEP_ANGLE = 90.0f;
	const float MIN_DEVIATION = 0.8f;
	const float MAX_DEVIATION = 3.0f;
	//speed
	const float SPEED = 50.0f;
	const float MIN_SPEED = -30.0f;
	const float MAX_SPEED = 180.0f;
	//timers
	const float MIN_TIME_ROTATION = 0.1f;
	const float MAX_TIME_ROTATION = 0.3f;
	const float TIME_TO_ATTACK = 0.01f;
	const float SPAWN_INTERVAL = 1.9f;
	const float STOP_INTERVAL = 2.0f;
	const float MOVE_INTERVAL = 3.0f;

	float angleToSpawn = 90.0f;
	//timers
	Timer attackTimer;
	Timer rotateTimer;
	Timer timerToStop;
	Timer timerToMove;
	Timer timerToSpawn;

	MoveToADirection mover;
	RandomNumbers randomNumbers;
	ShieldLine shieldLine;
	RotationVar rVar;

	EnemyRotator rot;
	Tmpl8::vec2 shieldDir = { 0 };

};

